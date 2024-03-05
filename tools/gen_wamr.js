// this will generate null0_api/src/null0_api_wamr.h

import { glob } from 'glob'
import YAML from 'yaml'
import { readFile } from 'node:fs/promises'
import { basename } from 'node:path'

function generateWamrWrapper (name, description, returns, args) {
  return `// ${description}
static void wamr_null0_${name}(wasm_exec_env_t exec_env, SOME ARGS) {
  return null0_${name}(SOME ARGS);
}`
}

/*
'i': i32
'I': i64
'f': f32
'F': f64
'r': externref (has to be the value of a uintptr_t variable)
'*': the parameter is a buffer address in WASM application
'~': the parameter is the byte length of WASM buffer as referred by preceding argument "*". It must follow after '*', otherwise, registration will fail
'$': the parameter is a string in WASM application
*/
function generateWasmSig (name, returns, args) {
  // if it returns struct, insert that as * to first param
  // pointers are *
  // string is $
  // buffer+len (like arrays or bytes) is *~
  // otherwise figure out i/I/f/F

  const mappedArgs = Object.keys(args).map((v, k, a) => {
    if (!v) {
      return null
    }
    const b = args[v]
    if (b === 'bytes') {
      delete a[k + 1]
    }
    return args[v]
  }).filter(a => a)

  const asa = mappedArgs.map(a => {
    switch (a) {
      case 'f32': return 'f'
      case 'i32': return 'i'
      case 'u32': return 'i'
      case 'bool': return 'i'
      case 'SfxPresetType': return 'i'
      case 'SfxWaveType': return 'i'
      case 'Key': return 'i'
      case 'Sound': return 'i'
      case 'Font': return 'i'
      case 'Image': return 'i'
      case 'ImageFilter': return 'i'
      case 'GamepadButton': return 'i'
      case 'MouseButton': return 'i'
      case 'string': return '$'
      case 'u32*': return '*'
      case 'Color': return '*'
      case 'SfxParams': return '*'
      case 'SfxParams*': return '*'
      case 'Vector*': return '*'
      case 'bytes': return '*~'
      default:
        console.log(`Unhandled arg: ${a}`)
    }
  })

  let r = ''
  if (returns === 'void') {
    r = ''
  } else if (['i32', 'u32', 'bool', 'Font', 'Image', 'Sound'].includes(returns)) {
    r = 'i'
  } else if (['f32'].includes(returns)) {
    r = 'f'
  } else if (['u64'].includes(returns)) {
    r = 'I'
  } else if (['Color', 'SfxParams', 'Vector', 'Dimensions', 'Rectangle', 'FileInfo'].includes(returns)) {
    asa.unshift('*')
  } else if (['bytes', 'string*'].includes(returns)) {
    r = '*'
  } else {
    console.log(`Unhandled return: ${returns}`)
  }

  return `{"${name}", wamr_null0_${name}, "(${asa.join('')})${r}"}`
}

const functions = []
const wasmsigs = []

for (const f of await glob('api/*.yml')) {
  const apiName = basename(f, '.yml')
  const api = YAML.parse(await readFile(f, 'utf8'))
  functions.push('')
  functions.push(`// ${apiName.toUpperCase()}`)
  for (const name of Object.keys(api)) {
    functions.push(generateWamrWrapper(name, api[name].description, api[name].returns, api[name].args))
    wasmsigs.push(generateWasmSig(name, api[name].returns, api[name].args))
  }
}

const rCode = `
// | GENERATED |

${functions.join('\n\n')}

static NativeSymbol null0_native_symbols[] = {
  ${wasmsigs.join(',\n  ')}
}

// | END GENERATED |
`

const newCode = (await readFile('null0_api/src/null0_api_wamr.h', 'utf8')).replace(/\/\/ \| GENERATED \|[\s\S]*\/\/ \| END GENERATED \|/gm, rCode)

console.log(newCode)
