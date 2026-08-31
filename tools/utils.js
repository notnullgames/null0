import { readFile, glob } from 'node:fs/promises'
import { basename } from 'node:path'
import YAML from 'yaml'

const NULL0_VERSION = JSON.parse(await readFile('package.json')).version


// Indent a string
export const indent = (str, count = 1, istr = ' ') => str.replace(/^/gm, istr.repeat(count))

export async function getApi() {
  // objects, not arrays: these are keyed by type name, and an array with
  // string properties serialises to `[]` (which silently emptied api.json)
  const out = { enums: {}, structs: {}, scalars: {} }
  for await (const f of glob('api/**/*.yml')) {
    const apiName = basename(f, '.yml')
    out[apiName] = {}
    for (const [name, info] of Object.entries(YAML.parse(await readFile(f, 'utf8')) || {})) {
      if (!['types', 'constants'].includes(apiName)) {
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

  out.constants.NULL0_VERSION = { value: NULL0_VERSION, type: 'string', description: 'The current tagged version of null0 engine' }

  return out
}

// check to make sure all my types are accounted for in definition
export async function checkTypes() {
  const { enums, structs, scalars, constants, ...a } = await getApi()
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

// Fill a generator's type-map for API types it doesn't name explicitly, so a
// new enum or struct in api/types.yml doesn't need an edit in all 23 cart
// generators. Existing entries always win - this only adds what's missing.
// `enumType` is what an enum crosses the boundary as (an int, in every
// language); `structType` is what a struct comes back as (a pointer into cart
// memory), either a string or a function of the type's name.
export function seedTypes(map, { enums, structs }, { enumType, structType }) {
  const resolve = (type, name) => (typeof type === 'function' ? type(name) : type)
  for (const name of Object.keys(enums || {})) {
    if (enumType !== undefined && !(name in map)) {
      map[name] = resolve(enumType, name)
    }
  }
  for (const name of Object.keys(structs || {})) {
    if (structType !== undefined && !(name in map)) {
      map[name] = resolve(structType, name)
    }
  }
  return map
}
