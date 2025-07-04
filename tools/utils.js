import { readFile } from 'node:fs/promises'
import { basename } from 'node:path'
import { glob } from 'glob'
import YAML from 'yaml'

// Indent a string
export const indent = (str, count = 1, istr = ' ') => str.replace(/^/gm, istr.repeat(count))

export async function getApi() {
  const out = { enums: [], structs: [], scalars: [] }
  for (const f of await glob('api/**/*.yml')) {
    const apiName = basename(f, '.yml')
    out[apiName] = {}
    for (const [name, info] of Object.entries(YAML.parse(await readFile(f, 'utf8')) || {})) {
      if (!['types', 'contants'].includes(apiName)) {
        if (!info.args) {
          info.args = {}
        }
        if (!info.returns) {
          info.returns = 'void'
        }
      }

      // sort types into sub-types
      if (apiName === 'types') {
        if (info.enums) {
          out.enums[name] = info
        } else if (info.members) {
          out.structs[name] = info
        } else {
          out.scalars[name] = info
        }
      } else {
        out[apiName][name] = info
      }
    }
  }
  return out
}

// check to make sure all my types are accounted for in definition
export async function checkTypes() {
  const { enums, structs, scalars, contants, ...a } = await getApi()
  const types = { ...enums, ...structs, ...scalars }
  let allTypes = []
  let missingTypes = []
  let unusedTypes = []
  const knownTypes = Object.keys(types)
  for (const [aname, afuncs] of Object.entries({ ...a })) {
    for (const [fname, f] of Object.entries(afuncs)) {
      allTypes.push(f.returns)
      const args = Object.values(f.args)
      allTypes.push(...args)
      if (!knownTypes.includes(f.returns)) {
        missingTypes.push(f.returns)
      }
      for (const aa of args) {
        if (!knownTypes.includes(aa)) {
          missingTypes.push(aa)
        }
      }
    }
  }

  for (const t of knownTypes) {
    if (!allTypes.includes(t)) {
      unusedTypes.push(t)
    }
  }

  allTypes = [...new Set(allTypes)].sort()
  missingTypes = [...new Set(missingTypes)].sort()
  unusedTypes = [...new Set(unusedTypes)].sort()
  return { types: allTypes, missing: missingTypes, unused: unusedTypes }
}
