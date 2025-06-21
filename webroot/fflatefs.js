// stupidly-minimal fs that uses fflate on the zip
// it's just enough to load js carts, and read files, but not much else

import * as fflate from 'fflate' // https://esm.sh/fflate/esm/browser.js

const FILETYPE_REGULAR_FILE = 4
const FILETYPE_DIRECTORY = 3

export default async function fflatefs(cartUrl) {
  const info = {}
  let ino = 4

  const data = fflate.unzipSync(new Uint8Array(await fetch(cartUrl).then((r) => r.arrayBuffer())), {
    filter: (file) => {
      if (file.name != 'main.wasm' && !file.name.endsWith('.DS_Store')) {
        info[file.name] = file
        info[file.name].type = file.name.endsWith('/') ? FILETYPE_DIRECTORY : FILETYPE_REGULAR_FILE
        info[file.name].ino = ino++
        return true
      }
    }
  })

  return {
    info,
    data,

    statSync(path, options = {}) {
      const p = path.replace(/^\//g, '')
      const i = info[p]
      const now = Math.floor(Date.now() / 1000)

      return {
        isFile: () => i?.type === FILETYPE_REGULAR_FILE,
        isDirectory: () => i?.type === FILETYPE_DIRECTORY,
        isSymbolicLink: () => false,
        isCharacterDevice: () => false,
        isBlockDevice: () => false,
        isFIFO: () => false,
        dev: 4,
        ino: i?.ino || 0,
        filetype: i?.type || 0,
        nlink: 0,
        size: i?.originalSize || 0,
        atimeMs: now,
        mtimeMs: now,
        ctimeMs: now
      }
    },

    readFileSync(path) {
      const p = path.replace(/^\//g, '')
      return data[p]
    }
  }
}
