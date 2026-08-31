// This will generate the API docs (used on the main website and in this repo).
//
// Two outputs:
//   API.md          the human-readable reference, in C-like pseudo-code
//   webroot/api.json  the same thing as data, plus every language's real
//                     declaration for each function, published to
//                     https://notnullgames.github.io/null0/api.json so the
//                     docs site can render a per-language API without keeping
//                     its own copy of any of this
import { writeFile } from 'node:fs/promises'
import { getApi } from './utils.js'
import { getLanguageDocs } from './lang_docs.js'

const out = [`The Null0 API is exposed to every cart language, and we try to keep the shape the same in all of them. This page describes what you can *do* with null0, in C-like pseudo-code.`, '', `For the exact syntax in your language, see [notnull.games/null0/languages](https://notnull.games/null0/languages) - every function below is rendered there in each language's own spelling, straight out of that language's generated bindings. The [languages](#languages) table at the bottom lists them.`]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()
const languages = await getLanguageDocs()

function describeFunction(name, def) {
  const out = []
  out.push('', `#### ${name}`)
  out.push('', def.description, '')
  out.push('```c')
  out.push(
    `${def.returns} ${name}(${Object.entries(def.args)
      .map(([aname, atype]) => `${atype} ${aname}`)
      .join(', ')})`
  )
  out.push('```', '')
  return out.join('\n')
}

out.push('', '## types', '', 'These are the types of parameters or things that functions can return.')

out.push('', '```c')
for (const [name, { description }] of Object.entries(scalars)) {
  out.push(`// ${description}`, name, '')
}
out.push('```', '')

out.push('', '### structs', '', 'This is a compound-object, like a row in a spreadsheet. These are used to pass multiple values as a single object.', '', '```c')
for (const [name, e] of Object.entries(structs)) {
  out.push(`// ${e.description}`, `struct ${name} {`)
  out.push(
    '  ' +
      Object.entries(e.members)
        .map(([name, type]) => `${type} ${name}`)
        .join(',\n  ')
  )
  out.push('}', '')
}
out.push('```', '')

out.push('', '### enums', '', 'This is a textual way to describe some possible options for an integer field.', '', '```c')
for (const [name, e] of Object.entries(enums)) {
  out.push(`// ${e.description}`, `enum ${name} {`)
  out.push(
    '  ' +
      Object.entries(e.enums)
        .map(([name, value]) => `${name} = ${value}`)
        .join(',\n  ')
  )
  out.push('}', '')
}
out.push('```', '')

out.push('', '### colors', '', 'These colors are pre-defined in most cart-languages:', '')
for (const [name, e] of Object.entries(constants)) {
  if (e.type !== 'Color') {
    continue
  }
  out.push('- `' + name + '`' + (e.description ? ` - ${e.description}` : ''))
}
out.push('')

out.push('', '### constants', '', 'Other defined constants:', '')
for (const [name, e] of Object.entries(constants)) {
  if (e.type === 'Color') {
    continue
  }
  out.push('- `' + name + '` = `' + e.value + '`' + (e.description ? ` - ${e.description}` : ''))
}
out.push('')

out.push('', '## callbacks', '', 'Callbacks are how you define your game. See [cart](https://notnull.games/null0/cart) for more info.', '')
for (const [name, def] of Object.entries(callbacks)) {
  out.push(describeFunction(name, def))
}

out.push('', '## api', '', 'These are what make up the things you can do in your game.', '')
const f = []
for (const [apiName, apiFuncs] of Object.entries(api)) {
  if (apiName === 'types' || apiName === 'constants') {
    continue
  }
  let s = `\n### ${apiName}\n`
  for (const [funcName, def] of Object.entries(apiFuncs)) {
    s += describeFunction(funcName, def) + '\n'
  }
  f.push(s)
}

out.push(f.join('---\n'))

// A cart language is only "supported" once it can express all of this, so the
// table doubles as a status list. The per-function declarations for each
// language are in api.json (and rendered on the website) - putting 154
// functions x 23 languages in here would bury the reference itself.
out.push('', '## languages', '', `A cart can be written in any of these. \`<image>\` is the docker image that builds it: \`docker run --rm -v .:/src -v .:/out konsumer/null0-cart-<image> mygame\`.`, '')
out.push('| language | image | kind | cart source | callback | bindings |')
out.push('| --- | --- | --- | --- | --- | --- |')
for (const [id, lang] of Object.entries(languages)) {
  const binding = lang.binding ? `[\`${lang.binding.split('/').pop()}\`](${lang.binding})${lang.reference ? ' (reference)' : ''}` : '-'
  out.push(`| ${lang.title} | \`${lang.image}\` | ${lang.kind} | \`${lang.file}\` | \`${lang.callback.split('\n').join(' ')}\` | ${binding} |`)
}
out.push('')

await writeFile('API.md', out.join('\n'))

// Everything above, as data. The docs site fetches this at build time, so it
// can never drift from api/*.yml the way a hand-copied page does.
await writeFile(
  'webroot/api.json',
  JSON.stringify(
    {
      version: constants.NULL0_VERSION.value,
      scalars,
      structs,
      enums,
      constants,
      callbacks,
      groups: Object.fromEntries(Object.entries(api).filter(([name, funcs]) => name !== 'types' && Object.keys(funcs).length)),
      languages
    },
    null,
    2
  ) + '\n'
)
