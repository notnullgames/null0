#!/usr/bin/env node

// this will build an assemblyscript cart for a dir of source (with index.ts & assets in it)

import { resolve } from 'path'
import { createWriteStream } from 'fs'
import { access } from 'fs/promises'
import { copy, remove } from 'fs-extra'
import prettyBytes from 'pretty-bytes'
import archiver from 'archiver'
import asc from "assemblyscript/asc"

let [,, target = 'release',name = process.env.npm_package_name || 'cart'] = process.argv

const dir = resolve('./src')

const entryPoint = resolve(dir, 'index.ts')
await access(entryPoint)

const options = [
  entryPoint,
  "--outFile", resolve(`build/${target}/${name}`, 'cart.wasm'),
  "--textFile", resolve(`build/${target}/${name}`, 'cart.wat'),
  '--runtime', 'stub',
  '--exportRuntime'
]

if (target === 'release') {
  options.push('--optimize')
  options.push('3')
}

const { error, stdout, stderr } = await asc.main(options)

await copy(resolve(dir, 'assets'), resolve(`build/${target}/${name}/assets`))
await remove(resolve(`build/${target}/${name}`, 'cart.js'))
await remove(resolve(`build/${target}/${name}`, 'cart.d.ts'))

const output = createWriteStream(resolve(`build/${target}/${name}.null0`))
const archive = archiver('zip', { zlib: { level: 9 }})

output.on('close', () => {
  console.log(`build/${target}/${name}.null0: ${prettyBytes(archive.pointer())} written.`)
})

archive.on('error', (err) => {
  throw err;
})

archive.pipe(output)
archive.directory(resolve(`build/${target}/${name}`), false)
await archive.finalize()
