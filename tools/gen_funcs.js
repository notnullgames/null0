// this will generate the host/functions.txt that is used for emscripten build

import { getAPI } from './shared.js'
import { writeFile } from 'fs/promises'

const out = ['_main', '_malloc', '_free']
for (const funcs of Object.values(await getAPI())) {
  for (const fname of Object.keys(funcs)) {
    out.push(`_null0_${fname}`)
  }
}

await writeFile('host/functions.txt', out.join('\n'))
