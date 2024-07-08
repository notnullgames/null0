// this will generate the web-host wrapper

import { getAPI } from './shared.js'
import { writeFile } from 'fs/promises'

const api = await getAPI()

const typeSizes = {
  Dimensions: 8,
  Vector: 8,
  Rectangle: 16,
  SfxParams: 96,
  Color: 4,
  FileInfo: 40
}


function outputFunction(name, {args, returns, description}) {
  const out = []

  const a = Object.keys(args)
  let retPtr
  if (['Color', 'Dimensions', 'FileInfo', 'Rectangle', 'Vector', 'SfxParams'].includes(returns)) {
    a.unshift('retPtr')
    retPtr = true
  }

  out.push(`// ${description}`)
  out.push(`${name}(${a.join(', ')}) {`)

  const preCode = []
  const postCode = []

  if (retPtr) {
    preCode.push(`  const hostRetPtr = host._malloc(${typeSizes[returns]})`)
    postCode.push(`  copyBytesToCart(hostRetPtr, ${typeSizes[returns]}, retPtr)`)
    postCode.push('  host._free(hostRetPtr)')
  }


  if (preCode.length) {
    out.push(...preCode)
  }

  if (postCode.length) {
    out.push(...postCode)
  }

  out.push(`}`)

  return out.join('\n')
}


// console.log(outputFunction('image_gradient', api.graphics.image_gradient))

for (const funcs of Object.values(await getAPI())) {
  for (const fname of Object.keys(funcs)) {
    console.log(outputFunction(fname, funcs[fname]))
  }
}