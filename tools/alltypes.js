// just output all tyles that are used

import { getAPI } from './shared.js'

const api = await getAPI()

const rets = new Set()
const args = new Set()

for (const cat of Object.values(api)) {
  for (const f of Object.values(cat)) {
    rets.add(f.returns)
    args.add(...Object.values(f.args || {}))
  }
}

console.log({ rets: [...rets], args: [...args].filter(v => v) })