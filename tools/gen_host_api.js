// this will generate the C host API (for wamr & web)
// BE CAREFUL! this should only be run to initially set things up. The actual functions will be manually written.

import { glob } from 'glob'
import YAML from 'yaml'
import { readFile, writeFile } from 'fs/promises'

function typeMap (arg) {
  switch (arg) {
    case 'u32': return 'uint32_t'
    case 'u32*': return 'uint32_t*'
    case 'i32': return 'int32_t'
    case 'u64': return 'uint64_t'
    case 'f32': return 'float'
    case 'Color': return 'uint32_t'
    case 'Image': return 'uint32_t'
    case 'Vector': return 'pntr_vector'
    case 'Vector*': return 'pntr_vector*'
    case 'Rectangle': return 'pntr_rectangle'
    case 'Sound': return 'uint32_t'
    case 'Dimensions': return 'pntr_vector'
    case 'ImageFilter': return 'pntr_filter'
    case 'Font': return 'uint32_t'
    case 'Key': return 'pntr_app_key'
    case 'GamepadButton': return 'pntr_app_gamepad_button'
    case 'MouseButton': return 'pntr_app_mouse_button'
    case 'bytes': return 'unsigned char*'
    case 'string': return 'char*'
    case 'string*': return 'char**'
    case 'FileInfo': return 'PHYSFS_Stat'
    default: return arg
  }
}

function genHostApi (name, { description, returns, args }) {
  const out = []
  out.push(`\n// ${description}`)
  out.push(`${typeMap(returns)} null0_${name}(${Object.keys(args).map(a => `${typeMap(args[a])} ${a}`).join(', ')}) {}`)

  return out
}

for (const f of await glob('api/*.yml')) {
  const api = YAML.parse(await readFile(f, 'utf8'))
  const api_name = f.replace(/^api\/(.+)\.yml$/g, '$1')
  const out = [`// Null0 host - ${api_name} - generated ${(new Date()).toISOString()}`, '#pragma once', '']

  if (['colors', 'filesystem', 'graphics', 'input', 'utilities', 'sound'].includes(api_name)) {
    out.push('#include <stdint.h>')
  }

  if (['filesystem', 'graphics', 'input'].includes(api_name)) {
    out.push('#include <stdbool.h>')
  }

  if (['filesystem'].includes(api_name)) {
    out.push('#include "physfs.h"');
    out.push(`char** null0_file_list_array;

// intialize filesystem
bool null0_init_filesystem(char* cart) {
  if (!PHYSFS_init("null0")) {
    printf("Could not init filesystem.\n");
    return false;
  }
  char* cartName = strtok(basename(cart), ".");

  if (strlen(cartName) > 127) {
    printf("Name is too long.\n");
    return false;
  }

  char pathname[134];
  snprintf(pathname, 134, "null0-%s", cartName);

  const char* writeDir = PHYSFS_getPrefDir("null0", pathname);

  if (!PHYSFS_mount(cart, NULL, 1)) {
    PHYSFS_deinit();
    printf("Could not mount filesystem.\n");
    return false;
  }

  // put writeDir at end of search-path (so user can overwrite any files)
  if (!PHYSFS_mount(writeDir, NULL, 1)) {
    PHYSFS_deinit();
    printf("Could not mount write-dir.\n");
    return false;
  }

  if (!PHYSFS_setWriteDir(writeDir)) {
    PHYSFS_deinit();
    printf("Could not set write-dir.\n");
    return false;
  }

  return true;
}

// unload the filesystem
void null0_unload_filesystem() {
  PHYSFS_deinit();
  PHYSFS_freeList(null0_file_list_array);
}
`)
  }

  if (['graphics'].includes(api_name)) {
    out.push('#include <pntr.h>')
  }

  if (['input'].includes(api_name)) {
    out.push('#include <pntr_app.h>')
  }

  if (['sound'].includes(api_name)) {
    out.push('#include "sfx_gen.h"')
    out.push(`
typedef enum SfxPresetType {
  SFX_COIN,
  SFX_LASER,
  SFX_EXPLOSION,
  SFX_POWERUP,
  SFX_HURT,
  SFX_JUMP,
  SFX_SELECT,
} SfxPresetType;

typedef enum SfxWaveType SfxWaveType;

// used by sfx_gen
int sfx_random(int range) {
  return null0_random_int(0, range);
}
`)
  }

  for (const func of Object.keys(api)) {
    out.push(genHostApi(func, api[func]).join('\n'))
  }
  await writeFile(`src/null0_api_${api_name}.h`, out.join('\n'))
}
