// Keeps the `cart:*_<lang>` npm scripts honest about --platform.
//
// Five images are amd64-only, and their cart scripts need
// `--platform linux/amd64` or `docker run` fails on an arm64 machine with
// "no matching manifest for linux/arm64/v8". That flag was maintained by hand
// and drifted the moment c3 turned out to be amd64-only too - so it is
// derived from tools/lang_docs.js now, and `npm run gen` fixes it.
//
// The scripts themselves stay hand-written: they encode which examples each
// language has (simple, demo, colorbars, tile, ...), which isn't in the
// registry.

import { readFile, writeFile } from 'node:fs/promises'
import { getLanguageDocs } from './lang_docs.js'

const FLAG = '--platform linux/amd64 '

const languages = await getLanguageDocs()
const pkg = JSON.parse(await readFile('package.json', 'utf8'))

// cart:simple_c3 -> c3, cart:wasi_demo_c -> c  (longest id wins, so `_c3`
// isn't read as `_c` plus a stray 3)
const langIds = Object.keys(languages).sort((a, b) => b.length - a.length)
const langOf = (script) => langIds.find((id) => script.endsWith(`_${id}`))

const changed = []
for (const [name, body] of Object.entries(pkg.scripts)) {
  if (!name.startsWith('cart:')) {
    continue
  }
  const lang = langOf(name)
  if (!lang) {
    throw new Error(`${name}: no language matches that suffix`)
  }

  const wanted = !!languages[lang].amd64Only
  const has = body.includes(FLAG.trim())
  if (wanted === has) {
    continue
  }

  pkg.scripts[name] = wanted ? body.replace('docker run --rm ', `docker run --rm ${FLAG}`) : body.replace(FLAG, '')
  changed.push(`${name} ${wanted ? '+' : '-'}platform`)
}

if (changed.length) {
  await writeFile('package.json', JSON.stringify(pkg, null, 2) + '\n')
}
console.log(changed.length ? `cart scripts: ${changed.join(', ')}` : 'cart scripts: already correct')
