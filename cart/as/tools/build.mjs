// this will build a cart
// this could be done with command-line and using global lib flag, but I wanted to inject all the color-defines as well (which require an import, and cannot be put in global lib)

import { resolve } from 'node:path'
import { access, writeFile, readFile } from 'node:fs/promises'
import archiver from 'archiver'
import { copy, remove } from 'fs-extra'
import prettyBytes from 'pretty-bytes'
import asc from 'assemblyscript/asc'
import tmp from 'tmp'

const [,, dirSource = 'src', name = process.env.npm_package_name || 'cart', dirOut = 'build'] = process.argv

const dir = resolve(dirSource)
const entryPoint = resolve(dir, 'main.ts')
await access(entryPoint)

const tmpobj = tmp.fileSync()

await writeFile(
  tmpobj.name,
  (await readFile('tools/null0.ts', 'utf8')) + '\n' + (await readFile(entryPoint, 'utf8'))
)

const { error, stdout, stderr } = await asc.main([
  tmpobj.name,
  '--outFile', resolve(`${dirOut}/${name}`, 'main.wasm'),
  '--textFile', resolve(`${dirOut}`, `${name}.wat`),
  '--optimize', 3
])

tmpobj.removeCallback()

await copy(resolve(dir, 'assets'), resolve(`${dirOut}/${name}/assets`))

const output = createWriteStream(resolve(`${dirOut}/${name}.null0`))
const archive = archiver('zip', { zlib: { level: 9 } })

output.on('close', () => {
  console.log(
    `${dirOut}/${name}.null0: ${prettyBytes(archive.pointer())} written.`
  )
})

archive.on('error', (err) => {
  throw err
})

archive.pipe(output)
archive.directory(resolve(`${dirOut}/${name}`), false)
await archive.finalize()
