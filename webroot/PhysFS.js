// uses an instantiated physfs filesystem from wasm for easywasi

export default class PhysFS {
  constructor(wasm) {
    this.wasm = wasm
  }

  appendFileSync(path, data, options = {}) {
    throw new Error('appendFileSync not implemented. This is a dummy fs.')
  }

  fsyncSync(fd) {
    throw new Error('fsyncSync not implemented. This is a dummy fs.')
  }

  linkSync(existingPath, newPath) {
    throw new Error('linkSync not implemented. This is a dummy fs.')
  }

  mkdirSync(path, options = {}) {
    throw new Error('mkdirSync not implemented. This is a dummy fs.')
  }

  readdirSync(path, options = {}) {
    throw new Error('readdirSync not implemented. This is a dummy fs.')
  }

  readFileSync(path, options = {}) {
    throw new Error('readFileSync not implemented. This is a dummy fs.')
  }

  readlinkSync(path, options = {}) {
    throw new Error('readlinkSync not implemented. This is a dummy fs.')
  }

  renameSync(oldPath, newPath) {
    throw new Error('renameSync not implemented. This is a dummy fs.')
  }

  rmdirSync(path, options = {}) {
    throw new Error('rmdirSync not implemented. This is a dummy fs.')
  }

  setFlagsSync(path, flags) {
    throw new Error('setFlagsSync not implemented. This is a dummy fs.')
  }

  statSync(path, options = {}) {
    throw new Error('statSync not implemented. This is a dummy fs.')
  }

  symlinkSync(target, path, type = 'file') {
    throw new Error('symlinkSync not implemented. This is a dummy fs.')
  }

  truncateSync(path, len = 0) {
    throw new Error('truncateSync not implemented. This is a dummy fs.')
  }

  unlinkSync(path) {
    throw new Error('unlinkSync not implemented. This is a dummy fs.')
  }

  utimesSync(path, atime, mtime) {
    throw new Error('utimesSync not implemented. This is a dummy fs.')
  }

  writeFileSync(path, data, options = {}) {
    throw new Error('writeFileSync not implemented. This is a dummy fs.')
  }
}
