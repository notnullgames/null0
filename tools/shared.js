import { glob } from 'glob'
import YAML from 'yaml'
import { readFile, writeFile } from 'node:fs/promises'
import { basename } from 'node:path'

export async function getAPI () {
  const out = {}
  for (const f of await glob('api/*.yml')) {
    const apiName = basename(f, '.yml')
    out[apiName] = YAML.parse(await readFile(f, 'utf8'))
  }
  return out
}

export async function codeTemplate (filename, code, write) {
  const rCode = `
// | GENERATED |

${code}

// | END GENERATED |
`
  const newCode = (await readFile(filename, 'utf8')).replace(/\/\/ \| GENERATED \|[\s\S]*\/\/ \| END GENERATED \|/gm, rCode)
  if (write) {
    await writeFile(filename, newCode)
  }
  return newCode
}
