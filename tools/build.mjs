#!/usr/bin/env node

// this will build an assemblyscript cart for a dir of source (with index.ts & assets in it)

import { resolve, basename } from 'path'
import { createWriteStream } from 'fs'
import { access } from 'fs/promises'
import { copy, remove } from 'fs-extra'
import prettyBytes from 'pretty-bytes'
import archiver from 'archiver'
import asc from "assemblyscript/asc"

let [,, dir, target='debug'] = process.argv
dir = resolve(dir)

const name = basename(dir).replace(/^.+_/g, '')

const entryPoint = resolve(dir, 'index.ts')
await access(entryPoint)

const options = [
  entryPoint,
  "--outFile", resolve(`build/wasm/${target}/${name}`, 'cart.wasm'),
  "--textFile", resolve(`build/wasm/${target}/${name}`, 'cart.wat'),
  '--runtime', 'stub',
  '--exportRuntime'
]

if (target === 'release') {
  options.push('--optimize')
  options.push('3')
}

const { error, stdout, stderr } = await asc.main(options)

await copy(resolve(dir, 'assets'), resolve(`build/wasm/${target}/${name}/assets`))

