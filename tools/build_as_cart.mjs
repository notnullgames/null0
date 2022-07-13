#!/usr/bin/env node

// this will build an assemblyscript cart for a dir of source (with index.ts in it)

import { resolve } from 'path'
import { createWriteStream } from 'fs'
import { access } from 'fs/promises'
import { copy, remove } from 'fs-extra'
import prettyBytes from 'pretty-bytes'
import archiver from 'archiver'
import asc from "assemblyscript/asc"

let [,,dir, name] = process.argv
dir = resolve(dir)

const entryPoint = resolve(dir, 'index.ts')
await access(entryPoint)

const { error, stdout, stderr, stats } = await asc.main([
  entryPoint,
  "--outFile", resolve(`build/cart/${name}`, 'cart.wasm'),
  "--optimize",
  "--stats",
  '--runtime', 'stub',
  '--exportRuntime'
])

await copy(resolve(dir, 'assets'), resolve(`build/cart/${name}/assets`))
await remove(resolve(`build/cart/${name}`, 'cart.js'))
await remove(resolve(`build/cart/${name}`, 'cart.d.ts'))

const output = createWriteStream(resolve(`build/cart/${name}.null0`))
const archive = archiver('zip', { zlib: { level: 9 }})

output.on('close', () => {
  console.log(`build/cart/${name}.null0: ${prettyBytes(archive.pointer())} written.`)
})

archive.on('error', (err) => {
  throw err;
})

archive.pipe(output)
archive.directory(resolve(`build/cart/${name}`), false)
await archive.finalize()
await remove(resolve(`build/cart/${name}`))
