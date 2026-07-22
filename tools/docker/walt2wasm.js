// compiles a .walt file to .wasm
const walt = require('walt-compiler')
const fs = require('fs')

const [input, output] = process.argv.slice(2)
const res = walt.compile(fs.readFileSync(input, 'utf8'), { filename: input })
fs.writeFileSync(output, Buffer.from(res.buffer()))
