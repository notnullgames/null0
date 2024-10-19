import { readFile, writeFile, mkdir, unlink } from 'fs/promises'
import { createWriteStream } from 'fs'
import asc from 'assemblyscript/asc'
import archiver from 'archiver'
import { copy } from 'fs-extra'

try {
  await mkdir('build')
} catch (e) {}

const { npm_package_name } = process.env
const archive = archiver('zip', { zlib: { level: 9 } })

console.log(`Building build/${npm_package_name}/main.wasm`)

// I inject the header instead of --lib, so I can do inline allocations (like new Color())
await writeFile('build/tmp.ts', (await readFile('null0.ts')) + '\n// user-code:\n' + (await readFile('src/main.ts')))

const { error, stdout, stderr, stats } = await asc.main([
  'build/tmp.ts',

  // only minimal seems to work in WAMR
  '--runtime', 'minimal',
  // '--runtime', 'incremental',
  // '--runtime', 'stub',

  // '--debug',
  // '--exportRuntime',
  '--config', './node_modules/@assemblyscript/wasi-shim/asconfig.json',
  '--optimizeLevel', '3',
  '--shrinkLevel', '2',
  '--noAssert',
  '--path', 'src',
  '--textFile', `build/${npm_package_name}.wat`,
  '--outFile', `build/${npm_package_name}/main.wasm`
], {})
await unlink('build/tmp.ts')

if (error) {
  console.error(stderr.toString())
} else {
  console.log(`Creating build/${npm_package_name}.null0`)
  await copy('src/assets', `build/${npm_package_name}/assets`)
  const output = createWriteStream(`build/${npm_package_name}.null0`)
  archive.pipe(output)
  archive.directory(`build/${npm_package_name}`, false)
  await archive.finalize()
  await copy(`build/${npm_package_name}.null0`, `../../build/cart/${npm_package_name}.null0`)
}
