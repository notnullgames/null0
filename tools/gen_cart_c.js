import { writeFile } from 'node:fs/promises'
import { getApi } from './utils.js'
import { cPreamble, cRetTypes, cArgsMap } from './c_header_common.js'

const out = [cPreamble]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

for (const [apiName, apiObj] of Object.entries(api)) {
  out.push('', `// ${apiName.toUpperCase()}`, '')
  for (const [funcName, { args, returns, description }] of Object.entries(apiObj)) {
    out.push(`// ${description}`)
    out.push(`NULL0_IMPORT("${funcName}")`)
    out.push(`extern ${cRetTypes[returns] || returns} ${funcName}(${cArgsMap(args)});`, '')
  }
}

await writeFile('carts/c/null0.h', out.join('\n'))
