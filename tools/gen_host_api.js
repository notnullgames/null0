// this will generate the C host API (for wamr & web)
// BE CAREFUL! this should only be run to initially set things up. The actual functions will be manually written.

import { glob } from 'glob'
import YAML from 'yaml'
import { readFile, writeFile } from 'fs/promises'

function typeMap (arg) {
  switch (arg) {
    case 'u32': return 'uint32_t'
    case 'u32*': return 'uint32_t*'
    case 'i32': return 'int32_t'
    case 'u64': return 'uint64_t'
    case 'f32': return 'float'
    case 'Color': return 'uint32_t'
    case 'Image': return 'uint32_t'
    case 'Vector': return 'pntr_vector'
    case 'Vector*': return 'pntr_vector*'
    case 'Rectangle': return 'pntr_rectangle'
    case 'Sound': return 'uint32_t'
    case 'Dimensions': return 'pntr_vector'
    case 'Font': return 'uint32_t'
    case 'Key': return 'pntr_app_key'
    case 'GamepadButton': return 'pntr_app_gamepad_button'
    case 'MouseButton': return 'pntr_app_mouse_button'
    case 'bytes': return 'unsigned char*'
    case 'string': return 'char*'
    default: return arg
  }
}

function genHostApi (name, { description, returns, args }) {
  const out = []
  out.push(`\n// ${description}`)
  out.push(`${typeMap(returns)} null0_${name}(${Object.keys(args).map(a => `${typeMap(args[a])} ${a}`).join(', ')}) {}`)

  return out
}

for (const f of await glob('api/*.yml')) {
  const api = YAML.parse(await readFile(f, 'utf8'))
  const api_name = f.replace(/^api\/(.+)\.yml$/g, '$1')
  const out = [`// Null0 host - ${api_name} - generated ${(new Date()).toISOString()}`, '#pragma once', '']

  if (['colors', 'filesystem', 'graphics', 'input', 'utilities', 'sound'].includes(api_name)) {
    out.push('#include <stdint.h>')
  }

  if (['filesystem', 'graphics', 'input'].includes(api_name)) {
    out.push('#include <stdbool.h>')
  }

  if (['sound'].includes(api_name)) {
    out.push('#include "sfx_gen.h"')
  }

  if (['graphics', 'input'].includes(api_name)) {
    out.push('#include "pntr.h"')
  }

  if (['input'].includes(api_name)) {
    out.push('#include "pntr_app.h"')
  }

  for (const func of Object.keys(api)) {
    out.push(genHostApi(func, api[func]).join('\n'))
  }
  await writeFile(`src/null0_api_${api_name}.h`, out.join('\n'))
}
