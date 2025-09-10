// This will generate the API docs in markdown (used on main webnsite and in this repo)
import { writeFile } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [`The Null0 API is exposed to several languages, but we try to keep the syntax mostly the same. See docs/templates in individual languages for exact syntax, this page is more about what you can do with null0. I will use C-like pseudo-code to describe everything here.`]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

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

await writeFile('API.md', out.join('\n'))
