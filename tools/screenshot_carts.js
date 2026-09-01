// Screenshots every built cart, for the gallery cards on the website.
//
// Runs the real web player headlessly - same null0.mjs, same loader, same
// wasm the browser runs - and grabs the canvas once the cart has drawn a few
// frames. That means a card can never show a picture of something the cart
// doesn't actually do.
//
//   node tools/screenshot_carts.js [--carts build/carts] [--host wbuild/host/null0.mjs] [--frames 30]
//
// Output is <carts>/<name>.png, so screenshots travel with the carts they
// depict and get published to github-pages by the same release step.

import { chromium } from 'playwright'
import { createServer } from 'node:http'
import { readFile, readdir, writeFile, copyFile, mkdir, rm } from 'node:fs/promises'
import { join, extname, basename } from 'node:path'

const arg = (name, fallback) => {
  const i = process.argv.indexOf(`--${name}`)
  return i === -1 ? fallback : process.argv[i + 1]
}

const cartsDir = arg('carts', 'build/carts')
const hostMjs = arg('host', 'wbuild/host/null0.mjs')
const frames = Number(arg('frames', 30))

const TYPES = { '.html': 'text/html', '.js': 'text/javascript', '.mjs': 'text/javascript', '.null0': 'application/octet-stream' }

// a cart is 640x480; the player scales to the element, so pin it to native size
const PAGE = `<!doctype html><meta charset="utf-8">
<style>html,body{margin:0;background:#000}null0-cart{display:block;width:640px;height:480px}</style>
<script type="module" src="/null0-cart.js"></script>
<null0-cart loading="eager"></null0-cart>
<script type="module">
  window.null0Ready = new Promise((resolve, reject) => {
    const el = document.querySelector('null0-cart')
    el.addEventListener('null0-loaded', () => resolve(true))
    el.addEventListener('null0-error', (e) => reject(new Error(String(e.detail))))
    el.setAttribute('src', new URLSearchParams(location.search).get('cart'))
  })
</script>`

async function main() {
  const carts = (await readdir(cartsDir)).filter((f) => f.endsWith('.null0')).sort()
  if (!carts.length) {
    console.error(`no carts in ${cartsDir} - run \`npm run carts\` first`)
    process.exit(1)
  }

  // assemble what the player needs: its own js, the emscripten host, the carts
  const root = 'build/screenshots-www'
  await rm(root, { recursive: true, force: true })
  await mkdir(join(root, 'carts'), { recursive: true })
  for (const f of ['null0.js', 'null0-cart.js', 'fflatefs.js']) {
    await copyFile(join('webroot', f), join(root, f))
  }
  await copyFile(hostMjs, join(root, 'null0.mjs'))
  for (const c of carts) {
    await copyFile(join(cartsDir, c), join(root, 'carts', c))
  }
  await writeFile(join(root, 'index.html'), PAGE)

  const server = createServer(async (req, res) => {
    const path = decodeURIComponent(req.url.split('?')[0])
    const file = path === '/' ? '/index.html' : path
    try {
      const body = await readFile(join(root, file))
      res.writeHead(200, { 'content-type': TYPES[extname(file)] || 'application/octet-stream' })
      res.end(body)
    } catch {
      res.writeHead(404).end('not found')
    }
  })
  await new Promise((resolve) => server.listen(0, resolve))
  const base = `http://localhost:${server.address().port}`

  // swiftshader: CI runners have no GPU, and the player needs webgl
  const browser = await chromium.launch({ args: ['--use-gl=swiftshader', '--enable-unsafe-swiftshader'] })
  const page = await browser.newPage({ viewport: { width: 640, height: 480 }, deviceScaleFactor: 1 })

  let ok = 0
  const failed = []
  const blank = []
  for (const cart of carts) {
    const name = basename(cart, '.null0')
    try {
      await page.goto(`${base}/?cart=/carts/${cart}`, { waitUntil: 'load' })
      await page.waitForFunction('window.null0Ready !== undefined', null, { timeout: 20000 })
      await page.evaluate('window.null0Ready')
      // let update() run - a cart that animates should be caught mid-motion,
      // not on its first blank frame
      await page.evaluate(
        (n) =>
          new Promise((resolve) => {
            let i = 0
            const tick = () => (++i >= n ? resolve() : requestAnimationFrame(tick))
            requestAnimationFrame(tick)
          }),
        frames
      )
      const shot = await page.locator('null0-cart').screenshot({ path: join(cartsDir, `${name}.png`) })

      // A cart that draws nothing produces a flat black frame, which looks
      // like a working screenshot until someone opens the gallery. Let the
      // browser decode its own screenshot and count what's actually in it.
      const colors = await page.evaluate(async (b64) => {
        const bmp = await createImageBitmap(await (await fetch(`data:image/png;base64,${b64}`)).blob())
        const c = new OffscreenCanvas(bmp.width, bmp.height)
        const ctx = c.getContext('2d')
        ctx.drawImage(bmp, 0, 0)
        const { data } = ctx.getImageData(0, 0, bmp.width, bmp.height)
        const seen = new Set()
        for (let i = 0; i < data.length; i += 4) {
          seen.add((data[i] << 16) | (data[i + 1] << 8) | data[i + 2])
          if (seen.size > 4) {
            break
          }
        }
        return seen.size
      }, shot.toString('base64'))

      if (colors < 2) {
        blank.push(name)
      }
      ok++
      console.log(`  ${name}.png${colors < 2 ? '  (BLANK)' : ''}`)
    } catch (error) {
      failed.push(`${name}: ${error.message.split('\n')[0]}`)
    }
  }

  await browser.close()
  server.close()

  console.log(`\n${ok}/${carts.length} screenshots -> ${cartsDir}`)
  if (blank.length) {
    // not fatal - a cart really can be all one colour - but it is almost
    // always a cart that stopped working
    console.log(`\n::warning::${blank.length} cart(s) rendered a single flat colour: ${blank.join(', ')}`)
  }
  if (failed.length) {
    console.log('\nfailed:')
    for (const f of failed) {
      console.log(`  ${f}`)
    }
    process.exitCode = 1
  }
}

await main()
