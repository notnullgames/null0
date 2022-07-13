#!/usr/bin/env node

// this will build an assemblyscript cart for a dir of source (with index.ts in it)

import { resolve } from 'path'
import { createWriteStream } from 'fs'
import { access } from 'fs/promises'
import asc from "assemblyscript/asc"

let [,, target = 'debug',name = process.env.npm_package_name || 'cart'] = process.argv

const dir = resolve('./src')

const entryPoint = resolve(dir, 'index.ts')
await access(entryPoint)

const options = [
  entryPoint,
  "--outFile", resolve(`build/${target}/${name}`, 'cart.wasm'),
  '--runtime', 'stub',
  '--stats',
  '--exportRuntime'
]

if (target === 'release') {
  options.push('--optimize')
  options.push('3')
} else {
  options.push("--textFile")
  options.push(resolve(`build/${target}/${name}`, 'cart.wat'))
}

const { error, stdout, stderr, stats } = await asc.main(options)

if (error) {
  console.error(error)
  console.log(stderr.toString())
  process.exit(1)
}else{
  console.log(stats)
}