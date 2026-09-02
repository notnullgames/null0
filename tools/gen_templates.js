// Generates a starter project per cart language into templates/<lang>/.
//
// Each of these is published as a `cart_<lang>` template repo, so the whole
// point is that it stays *small*. The old templates each vendored a copy of
// the language's null0 header, the entire emscripten web host, and a built
// .null0 - three things that go stale silently. None of that is needed now:
//
//   - the docker image bakes the bindings (or the interpreter), so there is
//     no header to copy into the project
//   - the web player is loaded from https://notnullgames.github.io/null0/,
//     so there is no host to vendor
//   - the cart itself is a build artifact, so it is gitignored
//
// What is left is your source, a package.json, two workflows and an index.html.

import { mkdir, writeFile, rm, readdir, copyFile, readFile } from 'node:fs/promises'
import { join, dirname, basename } from 'node:path'
import { getLanguageDocs, imageRef } from './lang_docs.js'

const languages = await getLanguageDocs()

const CDN = 'https://notnullgames.github.io/null0'
const RAW = 'https://raw.githubusercontent.com/notnullgames/null0/main'

// file-watch extensions for the dev-server, per language
const watchExts = (lang) => [...new Set([lang.file.split('.').pop(), 'png', 'json', 'wav', 'ogg', 'tmx', 'tsx'])].join(',')

// the docker invocation that builds the cart. CI runs as root and wants no
// --user; a developer's machine wants their own uid so /out isn't root-owned.
// `zip` inside the image appends to an existing archive, so a rebuild would
// leave files you deleted or renamed still inside the cart. Always start clean.
function dockerRun(lang, { ci = false } = {}) {
  const flags = ['--rm']
  if (!ci) {
    flags.push('--user $(id -u):$(id -g)')
  }
  if (lang.amd64Only) {
    flags.push('--platform linux/amd64')
  }
  return `rm -f webroot/mygame.null0 && docker run ${flags.join(' ')} -v ./cart:/src -v ./webroot:/out ${imageRef(lang)} mygame`
}

// js/python/lua/wren/cyber ship their bindings as editor-only definitions, and
// wat/walt/jik's are a reference list to copy from. Those are worth having in
// the project - but fetched on demand and gitignored, never committed, so they
// cannot drift from the engine.
const wantsLocalBinding = (lang) => !!lang.binding && (lang.kind === 'interpreted' || lang.reference)

function packageJson(lang) {
  const scripts = {
    build: `mkdir -p webroot && ${dockerRun(lang)}`,
    web: 'npx -y live-server webroot',
    'build:watch': `npx -y nodemon -e ${watchExts(lang)} --watch cart --exec 'npm run build'`,
    start: 'npm run build && npx -y npm-run-all -p web build:watch'
  }
  if (wantsLocalBinding(lang)) {
    const name = lang.binding.split('/').pop()
    scripts.bindings = `curl -sfL ${RAW}/${lang.binding} -o cart/${name}`
  }
  return JSON.stringify({ name: 'mygame', private: true, scripts }, null, 2) + '\n'
}

function gitignore(lang) {
  const out = ['.DS_Store', '.vscode', '', '# the cart is a build artifact', 'webroot/*.null0']
  if (wantsLocalBinding(lang)) {
    out.push('', '# fetched on demand with `npm run bindings`', `cart/${lang.binding.split('/').pop()}`)
  }
  return out.join('\n') + '\n'
}

const indexHtml = `<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>mygame</title>
    <!-- an import map has to come before any module script. only needed for
         players published before the release that made them import by
         absolute URL - safe to delete once you no longer care about those -->
    <script type="importmap">
      {
        "imports": {
          "@easywasm/wasi": "https://esm.sh/@easywasm/wasi@0.0.8",
          "fflate": "https://esm.sh/fflate@0.8.3/esm/browser.js"
        }
      }
    </script>
    <!-- the player is loaded from null0's own github-pages, so there is
         nothing to vendor here and nothing to keep up to date -->
    <script type="module" src="${CDN}/null0-cart.js"></script>
    <style>
      html,
      body {
        margin: 0;
        height: 100%;
      }
      body {
        display: flex;
        justify-content: center;
        align-items: center;
        background: #000;
      }
      null0-cart {
        width: min(100vw, 133.333vh);
      }
    </style>
  </head>
  <body>
    <null0-cart src="mygame.null0" loading="eager"></null0-cart>
  </body>
</html>
`

function publishWorkflow(lang) {
  return `name: Publish

on:
  push:
    branches: [main]
  workflow_dispatch:

permissions:
  contents: read
  pages: write
  id-token: write

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Build cart
        run: |
          mkdir -p webroot
          ${dockerRun(lang, { ci: true })}
      - uses: actions/upload-pages-artifact@v3
        with:
          path: ./webroot

  deploy:
    needs: build
    environment:
      name: github-pages
      url: \${{ steps.deployment.outputs.page_url }}
    runs-on: ubuntu-latest
    steps:
      - name: Deploy to GitHub Pages
        id: deployment
        uses: actions/deploy-pages@v4
`
}

function releaseWorkflow(lang) {
  return `name: Release

on:
  release:
    types: [published]

permissions:
  contents: write

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Build cart
        run: |
          mkdir -p webroot
          ${dockerRun(lang, { ci: true })}

      # The runtime mounts a zip appended to its own executable, so a
      # standalone game is just the current null0 runtime with the cart stuck
      # on the end. Nothing is compiled per-platform - the cart bytes are
      # identical in all of them, and in mygame.null0 itself.
      - name: Build standalone native games
        env:
          GH_TOKEN: \${{ github.token }}
        run: |
          set -euo pipefail
          mkdir -p dist
          for platform in linux_x86-64 macos windows_x64; do
            rm -rf runtime && mkdir runtime
            gh release download -R notnullgames/null0 --pattern "null0_\${platform}.zip" -D runtime
            unzip -oq "runtime/null0_\${platform}.zip" -d runtime
            if [ -f runtime/null0.exe ]; then
              cat runtime/null0.exe webroot/mygame.null0 > runtime/mygame.exe
              (cd runtime && zip -q "../dist/mygame_\${platform}.zip" mygame.exe)
            else
              cat runtime/null0 webroot/mygame.null0 > runtime/mygame
              chmod +x runtime/mygame
              (cd runtime && zip -q "../dist/mygame_\${platform}.zip" mygame)
            fi
          done
          ls -l dist

      - name: Attach cart and native games to release
        run: gh release upload \${{ github.event.release.tag_name }} webroot/mygame.null0 dist/mygame_*.zip
        env:
          GH_TOKEN: \${{ github.token }}
`
}

function readme(lang) {
  const out = []
  out.push(`# mygame`, '')
  out.push(`A starter [null0](https://notnull.games/null0) cart, in ${lang.title}.`, '')
  out.push(`Press **Use this template** to make your own, then search the project for \`mygame\` and rename it to whatever your game is called.`, '')

  out.push('## building', '')
  out.push(`Everything is built inside docker, so you never install ${lang.toolchain} yourself. All you need is [docker](https://docs.docker.com/get-started/get-docker/), plus [node](https://nodejs.org/) for the shortcuts below.`, '')
  out.push('```sh', 'npm start', '```', '')
  out.push('That builds `webroot/mygame.null0`, serves `webroot/`, and rebuilds whenever you edit something in `cart/`. To build once, without the server:', '')
  out.push('```sh', 'npm run build', '```', '')
  out.push('Or call docker yourself:', '')
  out.push('```sh', dockerRun(lang).split(' && ').join('\n'), '```', '')
  if (lang.amd64Only) {
    out.push(`> This image is \`linux/amd64\` only, so on Apple Silicon it runs under emulation. That works, it is just slow.`, '')
  }

  out.push('## writing your game', '')
  out.push(`Your code is in \`cart/${lang.file}\`. A cart implements the callbacks it cares about and the host skips the rest:`, '')
  out.push('```' + lang.highlight, lang.callback, '```', '')
  if (lang.entry) {
    out.push(`This toolchain also needs an entry point to exist, even though null0 never uses it for gameplay. Leave it empty:`, '')
    out.push('```' + lang.highlight, lang.entry, '```', '')
  }
  if (lang.notes?.length) {
    out.push(`### ${lang.title} notes`, '')
    for (const note of lang.notes) {
      out.push(`- ${note}`)
    }
    out.push('')
  }
  if (wantsLocalBinding(lang)) {
    const name = lang.binding.split('/').pop()
    out.push(`Run \`npm run bindings\` to drop the current \`${name}\` into \`cart/\` for your editor. It is gitignored on purpose - fetch it again whenever you want, rather than letting a stale copy rot in your repo.`, '')
  } else {
    out.push(`You do not need to copy any null0 bindings into this project - the docker image bakes the current [\`${lang.binding}\`](${RAW}/${lang.binding}) in for you.`, '')
  }

  out.push('## docs', '')
  out.push(`- [${lang.title} carts](https://notnull.games/null0/languages/${lang.id}) - the whole API, in ${lang.title}`)
  out.push('- [Anatomy of a cart](https://notnull.games/null0/cart) - callbacks, input, distribution')
  out.push('- [API reference](https://notnull.games/null0/api)')
  out.push('')

  out.push('## publishing', '')
  out.push('Two workflows come with this template:', '')
  out.push('- **Publish** builds the cart and deploys `webroot/` to github-pages on every push to `main`, so anyone can play your game in a browser without installing anything.')
  out.push('- **Release** attaches the cart *and* a standalone native game for every platform to any github release you create.')
  out.push('')
  out.push('So each release of your game ships:', '')
  out.push('| asset | what it is |')
  out.push('| --- | --- |')
  out.push('| `mygame.null0` | the cart itself - play it in a browser, or with `null0 mygame.null0` |')
  out.push('| `mygame_linux_x86-64.zip` | a single native executable, nothing to install |')
  out.push('| `mygame_macos.zip` | the same, universal (Intel and Apple Silicon) |')
  out.push('| `mygame_windows_x64.zip` | the same, as `mygame.exe` |')
  out.push('')
  out.push('### standalone games', '')
  out.push('The runtime mounts a zip appended to its own executable, so a standalone game is just the null0 runtime with your cart concatenated onto the end. The **Release** workflow does that for you, but it is one command by hand - grab a runtime from [null0 releases](https://github.com/notnullgames/null0/releases) and:', '')
  out.push('```sh', '# linux or mac', 'cat null0 mygame.null0 > mygame && chmod +x mygame', '```', '')
  out.push('```bat', 'REM windows', 'copy /b null0.exe+mygame.null0 mygame.exe', '```', '')
  out.push('The result is an ordinary executable that needs no arguments and no null0 installed. Players who already have the runtime can still just run `null0 mygame.null0`.', '')
  return out.join('\n')
}

// A cart project that names itself (rust's Cargo.toml) would arrive calling
// itself "simple", which breaks the template's "search for mygame and rename
// it" instruction. Rewrite those to mygame as we copy.
const MANIFESTS = new Set(['Cargo.toml', 'Cargo.lock'])

async function renameProject(file, exampleName) {
  const before = await readFile(file, 'utf8')
  const after = before.replaceAll(`name = "${exampleName}"`, 'name = "mygame"')
  if (after !== before) {
    await writeFile(file, after)
  }
}

// copy the language's `simple` cart in as the starting source
async function copyExample(from, to) {
  for (const entry of await readdir(from, { withFileTypes: true })) {
    const src = join(from, entry.name)
    const dest = join(to, entry.name)
    if (entry.isDirectory()) {
      await mkdir(dest, { recursive: true })
      await copyExample(src, dest)
    } else {
      await mkdir(dirname(dest), { recursive: true })
      await copyFile(src, dest)
      if (MANIFESTS.has(entry.name)) {
        await renameProject(dest, basename(from))
      }
    }
  }
}

await rm('templates', { recursive: true, force: true })

for (const lang of Object.values(languages)) {
  const dir = join('templates', lang.id)
  await mkdir(join(dir, '.github/workflows'), { recursive: true })
  await mkdir(join(dir, 'cart'), { recursive: true })
  await mkdir(join(dir, 'webroot'), { recursive: true })

  await copyExample(lang.example, join(dir, 'cart'))

  await writeFile(join(dir, 'README.md'), readme(lang))
  await writeFile(join(dir, 'package.json'), packageJson(lang))
  await writeFile(join(dir, '.gitignore'), gitignore(lang))
  await writeFile(join(dir, 'webroot/index.html'), indexHtml)
  await writeFile(join(dir, '.github/workflows/publish.yml'), publishWorkflow(lang))
  await writeFile(join(dir, '.github/workflows/release.yml'), releaseWorkflow(lang))
}

console.log(`generated ${Object.keys(languages).length} templates in templates/`)
