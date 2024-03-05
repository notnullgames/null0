// this will generate null0_api/src/null0_api_wamr.h

// TODO: fix file_read

import { getAPI, codeTemplate } from './shared.js'

// functions with manual implementations
// eventually I could automate
const blocklist = [
  'file_read',
  'get_write_dir'
]

// maps args to WAMR callback input arg-types
const getArgType = a => {
  switch (a) {
    case 'f32': return 'float32_t'
    case 'i32': return 'int32_t'
    case 'u32': return 'uint32_t'
    case 'bool': return 'bool'
    case 'SfxPresetType': return 'SfxPresetType'
    case 'SfxWaveType': return 'SfxWaveType'
    case 'Key': return 'int32_t'
    case 'Sound': return 'int32_t'
    case 'Font': return 'int32_t'
    case 'Image': return 'int32_t'
    case 'ImageFilter': return 'int32_t'
    case 'GamepadButton': return 'int32_t'
    case 'MouseButton': return 'int32_t'
    case 'string': return 'char*'
    case 'u32*': return 'uint32_t*'
    case 'Color': return 'Null0WasmColor*'
    case 'SfxParams': return 'SfxParams*'
    case 'SfxParams*': return 'SfxParams*'
    case 'Vector': return 'pntr_vector*'
    case 'Vector*': return 'pntr_vector*'
    case 'bytes': return 'unsigned char*'
    default:
      console.log(`Unhandled arg-type: ${a}`)
  }
}

// generate string for signatuire
// pointers are *
// string is $
// buffer+len (like arrays or bytes) is *~
// otherwise figure out i/I/f/F
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
const getSigArgs = a => {
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
      console.log(`Unhandled sig arg: ${a}`)
  }
}

function generateWamrWrapper (name, description, returns, args) {
  const argNames = Object.keys(args)
  const argTypes = Object.values(args).map(getArgType)

  // TODO: this will be wrapped with utils
  const argCallNames = Object.values(args).map((t, i) => {
    if (t === 'Color') {
      return `color_from_wasm_to_pntr(*${argNames[i]})`
    }
    return argNames[i]
  })
  let r = 'void'

  let wrapRet

  if (returns !== 'void') {
    if (returns === 'u32') {
      r = 'uint32_t'
    } else if (returns === 'i32') {
      r = 'int32_t'
    } else if (returns === 'string') {
      r = 'char*'
    } else if (returns === 'string*') {
      r = 'char**'
    } else if (returns === 'bytes') {
      r = 'char*'
    } else if (['Image', 'Font', 'Sound'].includes(returns)) {
      r = 'uint32_t'
    } else if (returns === 'f32') {
      r = 'float32_t'
    } else if (returns === 'bool') {
      r = 'bool'
    } else if (returns === 'u64') {
      r = 'uint64_t'
    } else if (returns === 'Color') {
      r = 'void'
      argNames.unshift('outColorValue')
      argTypes.unshift('Null0WasmColor*')
      wrapRet = ['color_from_pntr_to_wasm', 'outColorValue']
    } else if (returns === 'FileInfo') {
      r = 'void'
      argNames.unshift('outFileInfoValue')
      argTypes.unshift('PHYSFS_Stat*')
      wrapRet = ['fileinfo_from_physfs_to_wasm', 'outFileInfoValue']
    } else if (returns === 'Rectangle') {
      r = 'void'
      argNames.unshift('outRectangleValue')
      argTypes.unshift('pntr_rectangle*')
      wrapRet = ['rect_from_pntr_to_wasm', 'outRectangleValue']
    } else if (['Vector', 'Dimensions'].includes(returns)) {
      r = 'void'
      argNames.unshift('outVectorValue')
      argTypes.unshift('pntr_vector*')
      wrapRet = ['vector_from_pntr_to_wasm', 'outVectorValue']
    } else if (returns === 'SfxParams') {
      r = 'void'
      argNames.unshift('outSfxParamsValue')
      argTypes.unshift('SfxParams*')
      wrapRet = ['params_from_sfx_to_wasm', 'outSfxParamsValue']
    } else {
      console.log(`Unhandled return: ${returns}`)
    }
  }

  argNames.unshift('exec_env')
  argTypes.unshift('wasm_exec_env_t')

  let ret = ''
  if (r !== 'void') {
    ret = 'return '
  }

  if (wrapRet) {
    return `// ${description}
static ${r} wamr_null0_${name}(${argNames.map((a, i) => `${argTypes[i]} ${a}`).join(', ')}) {
  ${wrapRet[0]}(null0_${name}(${argCallNames.join(', ')}), ${wrapRet[1]});
}`
  } else {
    return `// ${description}
static ${r} wamr_null0_${name}(${argNames.map((a, i) => `${argTypes[i]} ${a}`).join(', ')}) {
  ${ret}null0_${name}(${argCallNames.join(', ')});
}`
  }
}

function generateWasmSig (name, returns, args) {
  // if it returns struct, insert that as * to first param
  // pointers are *
  // bytes are *
  // string is $
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

  const asa = mappedArgs.map(getSigArgs)

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
  } else if (['string'].includes(returns)) {
    r = 'i'
  } else {
    console.log(`Unhandled sig return: ${returns}`)
  }

  return `{"${name}", wamr_null0_${name}, "(${asa.join('')})${r}"}`
}

const functions = []
const wasmsigs = [
  '{"file_read", wamr_null0_file_read, "($*)i"}',
  '{"get_write_dir", wamr_null0_get_write_dir, "()i"}'
]

const a = await getAPI()
for (const apiName of Object.keys(a)) {
  const api = a[apiName]
  functions.push('')
  functions.push(`// ${apiName.toUpperCase()}`)
  for (const name of Object.keys(api)) {
    if (blocklist.includes(name)) {
      continue
    }
    functions.push(generateWamrWrapper(name, api[name].description, api[name].returns, api[name].args))
    wasmsigs.push(generateWasmSig(name, api[name].returns, api[name].args))
  }
}

const code = `${functions.join('\n\n')}

static NativeSymbol null0_wamr_callbacks[] = {
  ${wasmsigs.join(',\n  ')}
};`

await codeTemplate('null0_api/src/null0_api_wamr.h', code, true)
