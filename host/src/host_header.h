// setup utils and structures for host
// this will only be included in host.c

#include "host.h"
#include <time.h>
#ifdef _WIN32
#  include <sys/timeb.h>
#else
#  include <sys/time.h>
#endif
#include "exists_next_to_executable.h"
#include <ctype.h>

static pntr_app *null0_app;

static cvector_vector_type(pntr_image *) images;
static cvector_vector_type(pntr_font *) fonts;
static cvector_vector_type(pntr_sound *) sounds;
static cvector_vector_type(cute_tiled_map_t *) tilemaps;

// the shared gui context - carts build UI with the gui_* functions and never
// see this. host_update feeds input + begins the frame, gui_end (or the end
// of update) ends it, gui_draw renders it
static mu_Context *gui_ctx = NULL;
static bool gui_frame_ended = true;

// host-side allocations in cart memory, freed by cart_gc() after the current
// cart callback (load/update/event) returns
static cvector_vector_type(uint32_t) cart_allocations;

// allocate memory in the cart, tracked so cart_gc() can free it later
uint32_t cart_alloc_tracked(size_t size) {
  uint32_t ptr = cart_malloc(size);
  cvector_push_back(cart_allocations, ptr);
  return ptr;
}

// free everything the host allocated in cart memory since the last callback.
// this means host-returned pointers (struct/string returns) are only valid
// until the current cart callback returns - carts must copy what they need
void cart_gc() {
  for (size_t i = 0; i < cvector_size(cart_allocations); i++) {
    cart_free(cart_allocations[i]);
  }
  cvector_clear(cart_allocations);
}

// add an image to loaded images
uint32_t add_image(pntr_image *image) {
  if (image == NULL) {
    return 0;
  }
  uint32_t id = cvector_size(images);
  cvector_push_back(images, image);
  return id;
}

// add a font to loaded fonts
uint32_t add_font(pntr_font *font) {
  if (font == NULL) {
    return 0;
  }
  uint32_t id = cvector_size(fonts);
  cvector_push_back(fonts, font);
  return id;
}

// add a sound to loaded sounds
uint32_t add_sound(pntr_sound *sound) {
  if (sound == NULL) {
    return 0;
  }
  uint32_t id = cvector_size(sounds);
  cvector_push_back(sounds, sound);
  return id;
}

// add a tilemap to loaded tilemaps
uint32_t add_tilemap(cute_tiled_map_t *tilemap) {
  if (tilemap == NULL) {
    return 0;
  }
  uint32_t id = cvector_size(tilemaps);
  cvector_push_back(tilemaps, tilemap);
  return id;
}

// get an image by handle, NULL (with a warning) if out of range
pntr_image *get_image(uint32_t id) {
  if (id >= (uint32_t)cvector_size(images)) {
    pntr_app_log_ex(PNTR_APP_LOG_ERROR, "null0: invalid image handle: %u", id);
    return NULL;
  }
  return images[id];
}

// get a font by handle, NULL (with a warning) if out of range
pntr_font *get_font(uint32_t id) {
  if (id >= (uint32_t)cvector_size(fonts)) {
    pntr_app_log_ex(PNTR_APP_LOG_ERROR, "null0: invalid font handle: %u", id);
    return NULL;
  }
  return fonts[id];
}

// get a sound by handle, NULL (with a warning) if out of range
pntr_sound *get_sound(uint32_t id) {
  if (id >= (uint32_t)cvector_size(sounds)) {
    pntr_app_log_ex(PNTR_APP_LOG_ERROR, "null0: invalid sound handle: %u", id);
    return NULL;
  }
  return sounds[id];
}

// get a tilemap by handle, NULL (with a warning) if out of range
cute_tiled_map_t *get_tilemap(uint32_t id) {
  if (id >= (uint32_t)cvector_size(tilemaps)) {
    pntr_app_log_ex(PNTR_APP_LOG_ERROR, "null0: invalid tilemap handle: %u", id);
    return NULL;
  }
  return tilemaps[id];
}

// pntr_tiled builds one tile-array for a whole map and indexes it by gid with
// no bounds-check, so a gid past the end of the map's tilesets reads a garbage
// pntr_image and then draws from its pointer - garbage pixels or a segfault
// natively, "memory access out of bounds" on web. these keep every gid the
// host hands to pntr_tiled inside that array

// the number of tiles pntr_tiled allocates for a map (also its highest gid)
static int null0_tiled_tile_count(cute_tiled_map_t *map) {
  int count = 0;
  for (cute_tiled_tileset_t *tileset = map->tilesets; tileset != NULL;
    tileset = tileset->next) {
    count += tileset->tilecount;
  }
  return count;
}

// does this gid have a real tile behind it?
static bool null0_tiled_gid_valid(cute_tiled_map_t *map, int gid) {
  if (gid <= 0 || gid > null0_tiled_tile_count(map)) {
    return false;
  }
  for (cute_tiled_tileset_t *tileset = map->tilesets; tileset != NULL;
    tileset = tileset->next) {
    if (gid >= tileset->firstgid && gid < tileset->firstgid + tileset->tilecount) {
      return true;
    }
  }
  return false;
}

// drop tiles/objects that name a gid with no tile, returning how many
static int null0_tiled_fix_layer_gids(cute_tiled_map_t *map,
  cute_tiled_layer_t *layer) {
  int dropped = 0;
  while (layer != NULL) {
    for (int i = 0; i < layer->data_count; i++) {
      if (layer->data[i] != 0 &&
        !null0_tiled_gid_valid(map, cute_tiled_unset_flags(layer->data[i]))) {
        layer->data[i] = 0;
        dropped++;
      }
    }
    for (cute_tiled_object_t *object = layer->objects; object != NULL;
      object = object->next) {
      // gid 0 means "not a tile object" - pntr_tiled would draw the object's
      // box instead, so hide the object rather than clear its gid
      if (object->gid != 0 &&
        !null0_tiled_gid_valid(map, cute_tiled_unset_flags(object->gid))) {
        object->visible = 0;
        dropped++;
      }
    }
    dropped += null0_tiled_fix_layer_gids(map, layer->layers);
    layer = layer->next;
  }
  return dropped;
}

// an animated tile is drawn as another tile in its own tileset, so a frame
// pointing outside that tileset is the same bad index - drop those animations
static int null0_tiled_fix_animations(cute_tiled_map_t *map) {
  int dropped = 0;
  for (cute_tiled_tileset_t *tileset = map->tilesets; tileset != NULL;
    tileset = tileset->next) {
    for (cute_tiled_tile_descriptor_t *tile = tileset->tiles; tile != NULL;
      tile = tile->next) {
      for (int i = 0; i < tile->frame_count; i++) {
        if (tile->animation[i].tileid < 0 ||
          tile->animation[i].tileid >= tileset->tilecount) {
          tile->frame_count = 0;
          dropped++;
          break;
        }
      }
    }
  }
  return dropped;
}

// pntr_tiled blends layer->tintcolor into the tint when drawing object
// layers, but cute_tiled leaves tintcolor 0 when the layer has no tint, and
// pntr_tiled_color(0) is opaque black - default missing tints to white
static void null0_tiled_fix_layer_tints(cute_tiled_layer_t *layer) {
  while (layer != NULL) {
    if (layer->tintcolor == 0) {
      layer->tintcolor = 0xFFFFFFFF;
    }
    null0_tiled_fix_layer_tints(layer->layers);
    layer = layer->next;
  }
}

// load a Tiled map, fixing up missing layer tints and unusable gids (see above)
cute_tiled_map_t *null0_load_tiled(const char *filename) {
  cute_tiled_map_t *map = pntr_load_tiled(filename);
  if (map != NULL) {
    null0_tiled_fix_layer_tints(map->layers);
    int dropped =
      null0_tiled_fix_layer_gids(map, map->layers) + null0_tiled_fix_animations(map);
    if (dropped > 0) {
      pntr_app_log_ex(PNTR_APP_LOG_WARNING,
        "null0: %s has %d tile(s) with a gid outside its tilesets "
        "(highest gid is %d) - they will not be drawn",
        filename,
        dropped,
        null0_tiled_tile_count(map));
    }
  }
  return map;
}

// TILEMAP LAYERS, OBJECTS AND PROPERTIES
//
// a tilemap is the cart's initial state: layers, objects and properties are
// read-only, and the one thing a cart changes is a tile's gid (tile_set_tile),
// which is how a map keeps its own changing state - an opened chest is just a
// different gid, with its own tileset properties

typedef enum {
  LAYER_NONE = 0,
  LAYER_TILE = 1,
  LAYER_OBJECT = 2,
  LAYER_IMAGE = 3,
  LAYER_GROUP = 4
} TileLayerKind;

typedef enum {
  PROP_NONE = 0,
  PROP_INT = 1,
  PROP_BOOL = 2,
  PROP_FLOAT = 3,
  PROP_STRING = 4,
  PROP_COLOR = 5
} TilePropType;

// a custom property. only the member named by type is meaningful - gen_host
// copies this into cart memory, strings and all
typedef struct {
  char *name;
  TilePropType type;
  int32_t integer;
  float number;
  char *text;
} Null0TilemapProp;

// an object from an object-layer, as Tiled authored it
typedef struct {
  int32_t id;
  char *name;
  char *type;
  int32_t gid;
  float x;
  float y;
  float width;
  float height;
  float rotation;
  int32_t visible;
} Null0TilemapObject;

// pntr_tiled defines this but forgets to declare it in its header
PNTR_TILED_API void pntr_draw_tiled_layer(pntr_image *dst, cute_tiled_map_t *map, cute_tiled_layer_t *layer, int posX, int posY, pntr_color tint);

// layers are numbered depth-first, so the children of a group layer get their
// own indexes and a cart can address everything it sees in Tiled
static cute_tiled_layer_t *null0_tiled_layer_walk(cute_tiled_layer_t *layer, int *index, int wanted) {
  while (layer != NULL) {
    if ((*index)++ == wanted) {
      return layer;
    }
    cute_tiled_layer_t *found = null0_tiled_layer_walk(layer->layers, index, wanted);
    if (found != NULL) {
      return found;
    }
    layer = layer->next;
  }
  return NULL;
}

// get a layer by index, NULL (with a warning) if there is no such layer
static cute_tiled_layer_t *null0_tiled_layer_at(cute_tiled_map_t *map, int layer) {
  int index = 0;
  cute_tiled_layer_t *found = layer < 0 ? NULL : null0_tiled_layer_walk(map->layers, &index, layer);
  if (found == NULL) {
    pntr_app_log_ex(PNTR_APP_LOG_ERROR, "null0: invalid tilemap layer: %d", layer);
  }
  return found;
}

static int null0_tiled_layer_count_walk(cute_tiled_layer_t *layer) {
  int count = 0;
  while (layer != NULL) {
    count += 1 + null0_tiled_layer_count_walk(layer->layers);
    layer = layer->next;
  }
  return count;
}

// the number of layers in a tilemap (group layers count, and so do their children)
int null0_tile_layer_count(cute_tiled_map_t *map) {
  return null0_tiled_layer_count_walk(map->layers);
}

static int null0_tiled_layer_index_walk(cute_tiled_layer_t *layer, const char *name, int *index) {
  while (layer != NULL) {
    if (layer->name.ptr != NULL && strcmp(layer->name.ptr, name) == 0) {
      return *index;
    }
    (*index)++;
    int found = null0_tiled_layer_index_walk(layer->layers, name, index);
    if (found != -1) {
      return found;
    }
    layer = layer->next;
  }
  return -1;
}

// find a layer by name, -1 when there is none
int null0_tile_layer_index(cute_tiled_map_t *map, char *name) {
  int index = 0;
  return null0_tiled_layer_index_walk(map->layers, name, &index);
}

char *null0_tile_layer_name(cute_tiled_map_t *map, int layer) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  return (l != NULL && l->name.ptr != NULL) ? (char *)l->name.ptr : "";
}

TileLayerKind null0_tile_layer_type(cute_tiled_map_t *map, int layer) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  if (l == NULL || l->type.ptr == NULL) {
    return LAYER_NONE;
  }
  // "tilelayer" / "objectgroup" / "imagelayer" / "group" - same first-letter
  // test pntr_tiled uses when it draws
  switch (l->type.ptr[0]) {
    case 't': return LAYER_TILE;
    case 'o': return LAYER_OBJECT;
    case 'i': return LAYER_IMAGE;
    case 'g': return LAYER_GROUP;
    default: return LAYER_NONE;
  }
}

pntr_vector null0_tile_layer_size(cute_tiled_map_t *map, int layer) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  pntr_vector size = {0, 0};
  if (l != NULL) {
    size.x = l->width;
    size.y = l->height;
  }
  return size;
}

bool null0_tile_layer_visible(cute_tiled_map_t *map, int layer) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  return l != NULL && l->visible != 0;
}

pntr_vector null0_tile_map_size(cute_tiled_map_t *map) {
  pntr_vector size = {map->width, map->height};
  return size;
}

pntr_vector null0_tile_tile_size(cute_tiled_map_t *map) {
  pntr_vector size = {map->tilewidth, map->tileheight};
  return size;
}

// draw a single layer. pntr_draw_tiled_layer walks the layer's `next` siblings
// too, so unlink it for the duration - a group layer still draws its children
void null0_tile_draw_layer(pntr_image *dst, cute_tiled_map_t *map, int layer, int posX, int posY, pntr_color tint) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  if (dst == NULL || l == NULL) {
    return;
  }
  cute_tiled_layer_t *next = l->next;
  l->next = NULL;
  pntr_draw_tiled_layer(dst, map, l, posX, posY, tint);
  l->next = next;
}

// render one layer to a new image (map-sized, like tilemap_image)
pntr_image *null0_tile_layer_image(cute_tiled_map_t *map, int layer) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  if (l == NULL) {
    return NULL;
  }
  cute_tiled_layer_t *next = l->next;
  l->next = NULL;
  pntr_image *out = pntr_gen_image_tiled_layer(map, l, PNTR_WHITE);
  l->next = next;
  return out;
}

// get an object by index on an object-layer, NULL (with a warning) if there is none
static cute_tiled_object_t *null0_tiled_object_at(cute_tiled_map_t *map, int layer, int index) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  if (l != NULL && index >= 0) {
    int i = 0;
    for (cute_tiled_object_t *object = l->objects; object != NULL; object = object->next) {
      if (i++ == index) {
        return object;
      }
    }
  }
  if (l != NULL) {
    pntr_app_log_ex(PNTR_APP_LOG_ERROR, "null0: invalid tilemap object: %d", index);
  }
  return NULL;
}

int null0_tile_object_count(cute_tiled_map_t *map, int layer) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  int count = 0;
  if (l != NULL) {
    for (cute_tiled_object_t *object = l->objects; object != NULL; object = object->next) {
      count++;
    }
  }
  return count;
}

Null0TilemapObject null0_tile_object(cute_tiled_map_t *map, int layer, int index) {
  Null0TilemapObject out = {0, "", "", 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0};
  cute_tiled_object_t *object = null0_tiled_object_at(map, layer, index);
  if (object == NULL) {
    return out;
  }
  out.id = object->id;
  out.name = object->name.ptr != NULL ? (char *)object->name.ptr : "";
  out.type = object->type.ptr != NULL ? (char *)object->type.ptr : "";
  out.gid = object->gid;
  out.x = object->x;
  out.y = object->y;
  out.width = object->width;
  out.height = object->height;
  out.rotation = object->rotation;
  out.visible = object->visible ? 1 : 0;
  return out;
}

// find an object by name on an object-layer, -1 when there is none
int null0_tile_object_index(cute_tiled_map_t *map, int layer, char *name) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  if (l != NULL) {
    int index = 0;
    for (cute_tiled_object_t *object = l->objects; object != NULL; object = object->next) {
      if (object->name.ptr != NULL && strcmp(object->name.ptr, name) == 0) {
        return index;
      }
      index++;
    }
  }
  return -1;
}

// PROPERTIES: map, layer, object and tile (by gid) all carry the same kind of
// list, so they all go through these

static Null0TilemapProp null0_tiled_prop(cute_tiled_property_t *prop) {
  Null0TilemapProp out = {"", PROP_NONE, 0, 0.0f, ""};
  if (prop == NULL) {
    return out;
  }
  if (prop->name.ptr != NULL) {
    out.name = (char *)prop->name.ptr;
  }
  switch (prop->type) {
    case CUTE_TILED_PROPERTY_INT:
      out.type = PROP_INT;
      out.integer = prop->data.integer;
      break;
    case CUTE_TILED_PROPERTY_BOOL:
      out.type = PROP_BOOL;
      out.integer = prop->data.boolean ? 1 : 0;
      break;
    case CUTE_TILED_PROPERTY_FLOAT:
      out.type = PROP_FLOAT;
      out.number = prop->data.floating;
      break;
    case CUTE_TILED_PROPERTY_STRING:
      out.type = PROP_STRING;
      if (prop->data.string.ptr != NULL) {
        out.text = (char *)prop->data.string.ptr;
      }
      break;
    // cute_tiled hands file properties back as strings, so carts see them that way
    case CUTE_TILED_PROPERTY_FILE:
      out.type = PROP_STRING;
      if (prop->data.file.ptr != NULL) {
        out.text = (char *)prop->data.file.ptr;
      }
      break;
    case CUTE_TILED_PROPERTY_COLOR:
      out.type = PROP_COLOR;
      out.integer = (int32_t)prop->data.color;
      break;
    default:
      break;
  }
  return out;
}

static Null0TilemapProp null0_tiled_prop_named(cute_tiled_property_t *props, int count, const char *name) {
  for (int i = 0; i < count; i++) {
    if (props[i].name.ptr != NULL && strcmp(props[i].name.ptr, name) == 0) {
      return null0_tiled_prop(&props[i]);
    }
  }
  return null0_tiled_prop(NULL);
}

static Null0TilemapProp null0_tiled_prop_indexed(cute_tiled_property_t *props, int count, int index) {
  if (index < 0 || index >= count) {
    return null0_tiled_prop(NULL);
  }
  return null0_tiled_prop(&props[index]);
}

// the tileset entry describing a gid, NULL when the tile has no entry (which
// is normal - Tiled only writes one for tiles that carry something)
static cute_tiled_tile_descriptor_t *null0_tiled_tile_descriptor(cute_tiled_map_t *map, int gid) {
  for (cute_tiled_tileset_t *tileset = map->tilesets; tileset != NULL; tileset = tileset->next) {
    if (gid >= tileset->firstgid && gid < tileset->firstgid + tileset->tilecount) {
      for (cute_tiled_tile_descriptor_t *tile = tileset->tiles; tile != NULL; tile = tile->next) {
        if (tile->tile_index == gid - tileset->firstgid) {
          return tile;
        }
      }
      return NULL;
    }
  }
  return NULL;
}

Null0TilemapProp null0_tile_map_prop(cute_tiled_map_t *map, char *name) {
  return null0_tiled_prop_named(map->properties, map->property_count, name);
}

int null0_tile_map_prop_count(cute_tiled_map_t *map) {
  return map->property_count;
}

Null0TilemapProp null0_tile_map_prop_at(cute_tiled_map_t *map, int index) {
  return null0_tiled_prop_indexed(map->properties, map->property_count, index);
}

Null0TilemapProp null0_tile_layer_prop(cute_tiled_map_t *map, int layer, char *name) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  if (l == NULL) {
    return null0_tiled_prop(NULL);
  }
  return null0_tiled_prop_named(l->properties, l->property_count, name);
}

int null0_tile_layer_prop_count(cute_tiled_map_t *map, int layer) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  return l == NULL ? 0 : l->property_count;
}

Null0TilemapProp null0_tile_layer_prop_at(cute_tiled_map_t *map, int layer, int index) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  if (l == NULL) {
    return null0_tiled_prop(NULL);
  }
  return null0_tiled_prop_indexed(l->properties, l->property_count, index);
}

Null0TilemapProp null0_tile_object_prop(cute_tiled_map_t *map, int layer, int index, char *name) {
  cute_tiled_object_t *object = null0_tiled_object_at(map, layer, index);
  if (object == NULL) {
    return null0_tiled_prop(NULL);
  }
  return null0_tiled_prop_named(object->properties, object->property_count, name);
}

int null0_tile_object_prop_count(cute_tiled_map_t *map, int layer, int index) {
  cute_tiled_object_t *object = null0_tiled_object_at(map, layer, index);
  return object == NULL ? 0 : object->property_count;
}

Null0TilemapProp null0_tile_object_prop_at(cute_tiled_map_t *map, int layer, int index, int propIndex) {
  cute_tiled_object_t *object = null0_tiled_object_at(map, layer, index);
  if (object == NULL) {
    return null0_tiled_prop(NULL);
  }
  return null0_tiled_prop_indexed(object->properties, object->property_count, propIndex);
}

Null0TilemapProp null0_tile_gid_prop(cute_tiled_map_t *map, int gid, char *name) {
  cute_tiled_tile_descriptor_t *tile = null0_tiled_tile_descriptor(map, gid);
  if (tile == NULL) {
    return null0_tiled_prop(NULL);
  }
  return null0_tiled_prop_named(tile->properties, tile->property_count, name);
}

int null0_tile_gid_prop_count(cute_tiled_map_t *map, int gid) {
  cute_tiled_tile_descriptor_t *tile = null0_tiled_tile_descriptor(map, gid);
  return tile == NULL ? 0 : tile->property_count;
}

Null0TilemapProp null0_tile_gid_prop_at(cute_tiled_map_t *map, int gid, int index) {
  cute_tiled_tile_descriptor_t *tile = null0_tiled_tile_descriptor(map, gid);
  if (tile == NULL) {
    return null0_tiled_prop(NULL);
  }
  return null0_tiled_prop_indexed(tile->properties, tile->property_count, index);
}

// get the gid of a tile in a layer (by index) of a tilemap
int null0_tile_get_tile(cute_tiled_map_t *map, int layer, int column, int row) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  if (l == NULL) {
    return 0;
  }
  return pntr_layer_tile(l, column, row);
}

// set the gid of a tile in a layer (by index) of a tilemap
void null0_tile_set_tile(cute_tiled_map_t *map, int layer, int column, int row, int gid) {
  cute_tiled_layer_t *l = null0_tiled_layer_at(map, layer);
  if (l == NULL) {
    return;
  }
  if (gid != 0 && !null0_tiled_gid_valid(map, cute_tiled_unset_flags(gid))) {
    pntr_app_log_ex(PNTR_APP_LOG_ERROR, "null0: gid %d is not in this tilemap", gid);
    return;
  }
  pntr_set_layer_tile(l, column, row, gid);
}

// draw one tile of a tilemap, ignoring gids that have no tile
void null0_tile_draw_tile(pntr_image *dst, cute_tiled_map_t *map, int gid, int posX, int posY, pntr_color tint) {
  if (!null0_tiled_gid_valid(map, cute_tiled_unset_flags(gid))) {
    pntr_app_log_ex(PNTR_APP_LOG_ERROR, "null0: gid %d is not in this tilemap", gid);
    return;
  }
  pntr_draw_tiled_tile(dst, map, gid, posX, posY, tint);
}

// get a copy of a tile's image, so the cart can unload it like any other image
pntr_image *null0_tile_image(cute_tiled_map_t *map, int gid) {
  if (!null0_tiled_gid_valid(map, cute_tiled_unset_flags(gid))) {
    pntr_app_log_ex(PNTR_APP_LOG_ERROR, "null0: gid %d is not in this tilemap", gid);
    return NULL;
  }
  pntr_image *tileImage = pntr_tiled_tile_image(map, gid);
  if (tileImage == NULL) {
    return NULL;
  }
  return pntr_image_copy(tileImage);
}

// render a whole tilemap to a new image
pntr_image *null0_gen_image_tiled(cute_tiled_map_t *map) {
  return pntr_gen_image_tiled(map, PNTR_WHITE);
}

// begin a microui window (rect comes from the cart as a Rectangle)
bool null0_gui_begin_window(char *title, pntr_rectangle rect) {
  return mu_begin_window(gui_ctx, title, pntr_rectangle_to_mu_rect(rect));
}

// a checkbox that takes and returns its state by value
bool null0_gui_checkbox(char *label, bool state) {
  int s = state ? 1 : 0;
  mu_checkbox(gui_ctx, label, &s);
  return s != 0;
}

// a slider that takes and returns its value by value
float null0_gui_slider(float value, float low, float high) {
  mu_Real v = value;
  mu_slider(gui_ctx, &v, low, high);
  return (float)v;
}

// set the current layout row (microui takes the count first, our ABI puts it after the array)
void null0_gui_layout_row(int32_t *widths, int32_t numWidths, int32_t height) {
  mu_layout_row(gui_ctx, numWidths, widths, height);
}

// end the gui frame (also called automatically after update if the cart didn't)
void null0_gui_end() {
  if (gui_ctx != NULL && !gui_frame_ended) {
    mu_end(gui_ctx);
    gui_frame_ended = true;
  }
}

// draw the gui to an image
void null0_gui_draw(pntr_image *dst) {
  if (gui_ctx != NULL) {
    pntr_draw_microui(dst, gui_ctx);
  }
}

// SAM TTS function - generates WAV data from text
// sets byteLength and returns pointer to WAV bytes
char* sam_tts_sound(char* text, bool phonetic, int pitch, int speed, int throat, int mouth, bool sing, unsigned int* byteLength) {
    if (text == NULL || byteLength == NULL) return NULL;
    
    // Prepare input string (SAM expects uppercase)
    char input[512];
    int len = strlen(text);
    if (len >= 500) len = 499; // Leave room for terminator and bracket
    
    int i;
    for (i = 0; i < len; i++) {
        input[i] = toupper((int)text[i]);
    }
    input[i] = '\0';
    
    // Set SAM parameters
    SetPitch((unsigned char)pitch);
    SetSpeed((unsigned char)speed); 
    SetMouth((unsigned char)mouth);
    SetThroat((unsigned char)throat);
    
    if (sing) {
        EnableSingmode();
    }
    
    // Handle phonetic vs text input
    if (!phonetic) {
        strcat(input, "[");
        if (!TextToPhonemes((unsigned char*)input)) {
            return NULL;
        }
    } else {
        strcat(input, "\x9b");
    }
    
    // Generate speech
    SetInput(input);
    if (!SAMMain()) {
        return NULL;
    }
    
    // Get the raw audio buffer
    char* rawBuffer = GetBuffer();
    int rawLength = GetBufferLength() / 50; // SAM divides by 50 for WAV output
    
    if (rawBuffer == NULL || rawLength <= 0) {
        return NULL;
    }
    
    // Calculate WAV file size
    unsigned int wavSize = 44 + rawLength; // WAV header (44 bytes) + data
    char* wavData = (char*)malloc(wavSize);
    if (wavData == NULL) {
        return NULL;
    }
    
    // Build WAV header
    char* ptr = wavData;
    
    // RIFF header
    memcpy(ptr, "RIFF", 4); ptr += 4;
    unsigned int filesize = rawLength + 36;
    memcpy(ptr, &filesize, 4); ptr += 4;
    memcpy(ptr, "WAVE", 4); ptr += 4;
    
    // Format chunk
    memcpy(ptr, "fmt ", 4); ptr += 4;
    unsigned int fmtlength = 16;
    memcpy(ptr, &fmtlength, 4); ptr += 4;
    unsigned short format = 1; // PCM
    memcpy(ptr, &format, 2); ptr += 2;
    unsigned short channels = 1;
    memcpy(ptr, &channels, 2); ptr += 2;
    unsigned int samplerate = 22050;
    memcpy(ptr, &samplerate, 4); ptr += 4;
    memcpy(ptr, &samplerate, 4); ptr += 4; // bytes/second
    unsigned short blockalign = 1;
    memcpy(ptr, &blockalign, 2); ptr += 2;
    unsigned short bitspersample = 8;
    memcpy(ptr, &bitspersample, 2); ptr += 2;
    
    // Data chunk
    memcpy(ptr, "data", 4); ptr += 4;
    memcpy(ptr, &rawLength, 4); ptr += 4;
    memcpy(ptr, rawBuffer, rawLength);
    
    *byteLength = wavSize;
    return wavData;
}

// wrapper around SAM TTS function to return a sound int
pntr_sound* null0_tts_sound(char* text, bool phonetic, int pitch, int speed, int throat, int mouth, bool sing) {
  if (pitch == 0) {
    pitch = 64;
  }
  if (speed == 0) {
    speed = 72;
  }
  if (throat == 0) {
    throat = 128;
  }
  if (mouth == 0) {
    mouth = 128;
  }
  unsigned int byteLength = 0;
  char* wavData = sam_tts_sound(text, phonetic, pitch, speed, throat, mouth, sing, &byteLength);
  pntr_sound* sound = pntr_load_sound_from_memory(PNTR_APP_SOUND_TYPE_WAV, (unsigned char*)wavData, byteLength);
  // pntr_unload_memory(wavData);
  return sound;
}

// wrapper around pntr_app_sfx_sound
pntr_sound* null0_sfx_sound(SfxParams* params) {
  return pntr_app_sfx_sound(null0_app, params);
}

typedef enum SfxPresetType {
  SFX_COIN,
  SFX_LASER,
  SFX_EXPLOSION,
  SFX_POWERUP,
  SFX_HURT,
  SFX_JUMP,
  SFX_SELECT,
  SFX_SYNTH
} SfxPresetType;


// generate randomized SfxParams
SfxParams null0_sfx_generate(int type) {
  SfxParams sp = {};
  switch (type) {
    case SFX_COIN:
      pntr_app_sfx_gen_pickup_coin(null0_app, &sp);
      break;
    case SFX_LASER:
      pntr_app_sfx_gen_laser_shoot(null0_app, &sp);
      break;
    case SFX_EXPLOSION:
      pntr_app_sfx_gen_explosion(null0_app, &sp);
      break;
    case SFX_POWERUP:
      pntr_app_sfx_gen_powerup(null0_app, &sp);
      break;
    case SFX_HURT:
      pntr_app_sfx_gen_hit_hurt(null0_app, &sp);
      break;
    case SFX_JUMP:
      pntr_app_sfx_gen_jump(null0_app, &sp);
      break;
    case SFX_SELECT:
      pntr_app_sfx_gen_blip_select(null0_app, &sp);
      break;
    case SFX_SYNTH:
      pntr_app_sfx_gen_synth(null0_app, &sp);
      break;
    default:
      pntr_app_sfx_gen_pickup_coin(null0_app, &sp);
      break;
  }
  return sp;
}

// copy a string from cart to host
char *copy_string_from_cart(uint32_t cart_pointer) {
  uint32_t size = cart_strlen(cart_pointer) + 1;
  char *ret = malloc(size);
  mem_from_cart(ret, cart_pointer, size);
  return ret;
}

// copy a string from host to cart
uint32_t copy_string_to_cart(char *host_pointer) {
  if (host_pointer == NULL) {
    host_pointer = "";
  }
  uint32_t size = strlen(host_pointer) + 1;
  uint32_t ret = cart_alloc_tracked(size);
  mem_to_cart(ret, (void *)host_pointer, size);
  return ret;
}

// copy a rectangle from cart to host
pntr_rectangle copy_rectangle_from_cart(uint32_t rectPtr) {
  pntr_rectangle ret = {};
  mem_from_cart(&ret, rectPtr, sizeof(pntr_rectangle));
  return ret;
}

// copy a color from cart to host
pntr_color copy_color_from_cart(uint32_t colorPtr) {
  CartColor c = {};
  mem_from_cart(&c, colorPtr, sizeof(CartColor));
  pntr_color ret = pntr_new_color(c.r, c.g, c.b, c.a);
  return ret;
}

// copy a color form host to cart
uint32_t copy_color_to_cart(pntr_color color) {
  CartColor *c = malloc(sizeof(CartColor));
  c->r = color.rgba.r;
  c->g = color.rgba.g;
  c->b = color.rgba.b;
  c->a = color.rgba.a;
  uint32_t ret = cart_alloc_tracked(sizeof(CartColor));
  mem_to_cart(ret, c, sizeof(CartColor));
  return ret;
}

// Allocate & copy memory from cart to host
void *copy_memory_from_cart(uint32_t src, uint32_t size) {
  void *dest = malloc(size);
  mem_from_cart(dest, src, size);
  return dest;
}

// Allocate & copy memory from host to cart
uint32_t copy_memory_to_cart(void *src, uint32_t size) {
  uint32_t dest = cart_alloc_tracked(size);
  mem_to_cart(dest, src, size);
  return dest;
}

bool host_init(pntr_app *app) {
  // First try to find embedded cart in executable
  char* exe_path = get_executable_path();
  bool has_embedded = exe_path && fs_has_embedded_cart(exe_path);

  if (has_embedded && !app->argFile) {
    // Use embedded cart
    app->argFile = strdup(exe_path);
  } else {
    // Fallback to external file
    char* main_path = file_exists_next_to_executable("main.null0");
    if (!app->argFile && main_path) {
      app->argFile = strdup(main_path);
    }
    free(main_path);
  }
  
  if (exe_path) free(exe_path);

  if (!app->argFile) {
    pntr_app_log(PNTR_APP_LOG_ERROR, "Usage: null <CART>");
    return false;
  }

  null0_app = app;

  if (!PHYSFS_init("/")) {
    pntr_app_log(PNTR_APP_LOG_ERROR, "Could not start filesystem.");
    return false;
  }

  uint32_t cartSize = 0;
  unsigned char *cartBytes = NULL;
  uint32_t wasmSize = 0;
  unsigned char *wasmBytes = NULL;

  // Check if we're using embedded cart
  if (has_embedded) {
    // Mount the executable as PhysFS archive
    if (!fs_mount_embedded_cart(app->argFile)) {
      PHYSFS_deinit();
      pntr_app_log(PNTR_APP_LOG_ERROR, "Could not mount embedded cart.");
      return false;
    }
    
    // Load main.wasm from mounted archive
    wasmBytes = fs_load_file("main.wasm", &wasmSize);
    if (wasmSize == 0) {
      PHYSFS_deinit();
      pntr_app_log(PNTR_APP_LOG_ERROR, "Could not load main.wasm from embedded cart.");
      return false;
    }
  } else {
    // Original external file logic
    cartBytes = fs_load_file_real(app->argFile, &cartSize);

    if (!cartSize) {
      if (cartBytes) {
        free(cartBytes);
      }
      pntr_app_log(PNTR_APP_LOG_ERROR, "Could not load cart.");
      return false;
    }

    DetectFileType cartType = fs_parse_magic_bytes(*(uint32_t *)cartBytes);

    if (cartType == FILE_TYPE_ZIP) {
      if (!PHYSFS_mountMemory(cartBytes, cartSize, NULL, "cart.zip", NULL, 1)) {
        PHYSFS_deinit();
        free(cartBytes);
        pntr_app_log(PNTR_APP_LOG_ERROR, "Could not mount cart.");
        return false;
      }
      wasmBytes = fs_load_file("main.wasm", &wasmSize);
      if (wasmSize == 0) {
        free(cartBytes);
        pntr_app_log(PNTR_APP_LOG_ERROR, "Could not load main.wasm.");
        return false;
      }
    } else if (cartType == FILE_TYPE_WASM) {
      wasmSize = cartSize;
      wasmBytes = cartBytes;
    } else {
      free(cartBytes);
      pntr_app_log(PNTR_APP_LOG_ERROR, "Only wasm/zip cart-files are supported.");
      return false;
    }
  }

  // give the cart somewhere to save things (save_image, and friends)
  fs_set_write_dir(app->argFile);

  add_image(app->screen);
  add_font(pntr_load_font_default());

  // there is no "default tilemap", so reserve handle 0 as invalid
  cvector_push_back(tilemaps, (cute_tiled_map_t *)NULL);

  // the shared gui context, rendered with the default font
  gui_ctx = pntr_load_microui(fonts[0]);

  bool ret = cart_init(app, wasmBytes, wasmSize);
  // NOTE: Do NOT free cartBytes here! PHYSFS_mountMemory keeps a pointer to it.
  // It will be freed when PHYSFS_deinit() is called at shutdown.
  // if (cartBytes) free(cartBytes);
  free(wasmBytes);
  cart_gc();
  return ret;
}

bool host_update(pntr_app *app) {
  if (gui_ctx != NULL) {
    // feed input into the gui and begin the frame - carts build UI in update
    pntr_microui_update(gui_ctx, app);
    gui_frame_ended = false;
  }
  cart_update();
  cart_gc();
  if (gui_ctx != NULL && !gui_frame_ended) {
    mu_end(gui_ctx);
    gui_frame_ended = true;
  }
  return true;
}

// this maps keys to joystick buttons (for non-libretro)
static pntr_app_gamepad_button cart_map_key(pntr_app_key key) {
  switch (key) {
  case PNTR_APP_KEY_UP:
    return PNTR_APP_GAMEPAD_BUTTON_UP;
  case PNTR_APP_KEY_DOWN:
    return PNTR_APP_GAMEPAD_BUTTON_DOWN;
  case PNTR_APP_KEY_LEFT:
    return PNTR_APP_GAMEPAD_BUTTON_LEFT;
  case PNTR_APP_KEY_RIGHT:
    return PNTR_APP_GAMEPAD_BUTTON_RIGHT;
  case PNTR_APP_KEY_Q:
    return PNTR_APP_GAMEPAD_BUTTON_LEFT_SHOULDER;
  case PNTR_APP_KEY_W:
    return PNTR_APP_GAMEPAD_BUTTON_RIGHT_SHOULDER;
  case PNTR_APP_KEY_Z:
    return PNTR_APP_GAMEPAD_BUTTON_B;
  case PNTR_APP_KEY_X:
    return PNTR_APP_GAMEPAD_BUTTON_A;
  case PNTR_APP_KEY_A:
    return PNTR_APP_GAMEPAD_BUTTON_Y;
  case PNTR_APP_KEY_S:
    return PNTR_APP_GAMEPAD_BUTTON_X;
  case PNTR_APP_KEY_LEFT_SHIFT:
    return PNTR_APP_GAMEPAD_BUTTON_SELECT;
  case PNTR_APP_KEY_RIGHT_SHIFT:
    return PNTR_APP_GAMEPAD_BUTTON_SELECT;
  case PNTR_APP_KEY_ENTER:
    return PNTR_APP_GAMEPAD_BUTTON_START;
  default:
    return PNTR_APP_GAMEPAD_BUTTON_UNKNOWN;
  }
}

// microui takes mouse buttons as edges, and on the web those edges get lost:
// browser events land between frames, and pntr_app_pre_events copies
// mouseButtonsDown into mouseButtonsDownLast at the top of the frame - so by
// the time pntr_microui_update tests `down && !downLast` the press already
// looks old. Hover kept working (it only needs a position), which is why the
// gui looked alive but nothing was clickable. Feeding microui straight from
// the event is unambiguous. Safe alongside pntr_microui_update's own
// handling: mu_input_mouse* just OR/AND bits, so a duplicate is a no-op.
static int null0_mu_mouse_button(pntr_app_mouse_button button) {
  switch (button) {
  case PNTR_APP_MOUSE_BUTTON_LEFT:
    return MU_MOUSE_LEFT;
  case PNTR_APP_MOUSE_BUTTON_RIGHT:
    return MU_MOUSE_RIGHT;
  case PNTR_APP_MOUSE_BUTTON_MIDDLE:
    return MU_MOUSE_MIDDLE;
  default:
    return 0;
  }
}

void host_event(pntr_app_event *event) {
  // TODO: it would be cool to handle wheel, DnD, cheat & save events as well
  if (event->type == PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN) {
    if (gui_ctx != NULL) {
      int button = null0_mu_mouse_button(event->mouseButton);
      if (button) {
        mu_input_mousedown(gui_ctx, (int)event->mouseX, (int)event->mouseY, button);
      }
    }
    cart_mouseDown(event->mouseButton);
  }
  if (event->type == PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP) {
    if (gui_ctx != NULL) {
      int button = null0_mu_mouse_button(event->mouseButton);
      if (button) {
        mu_input_mouseup(gui_ctx, (int)event->mouseX, (int)event->mouseY, button);
      }
    }
    cart_mouseUp(event->mouseButton);
  }
  if (event->type == PNTR_APP_EVENTTYPE_MOUSE_MOVE) {
    cart_mouseMoved(event->mouseX, event->mouseY);
  }
  if (event->type == PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN) {
    cart_buttonDown(event->gamepadButton, event->gamepad);
  }
  if (event->type == PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP) {
    cart_buttonUp(event->gamepadButton, event->gamepad);
  }

  // these are fired & also mapped to button-events
  if (event->type == PNTR_APP_EVENTTYPE_KEY_DOWN) {
    cart_keyDown(event->key);
#ifndef PNTR_APP_LIBRETRO
    pntr_app_gamepad_button b = cart_map_key(event->key);
    if (b != PNTR_APP_GAMEPAD_BUTTON_UNKNOWN) {
      cart_buttonDown(b, 9999);
    }
#endif
  }
  if (event->type == PNTR_APP_EVENTTYPE_KEY_UP) {
    cart_keyUp(event->key);
#ifndef PNTR_APP_LIBRETRO
    pntr_app_gamepad_button b = cart_map_key(event->key);
    if (b != PNTR_APP_GAMEPAD_BUTTON_UNKNOWN) {
      cart_buttonUp(b, 9999);
    }
#endif
  }
  cart_gc();
}

// called from carts: these are lil wrappers/helpers to put things in right shape
// return unix-time, in ms
uint64_t null0_current_time() {
#ifdef _WIN32
  struct _timeb tb;
  _ftime64_s(&tb);
  return (uint64_t)tb.time * 1000ULL + (uint64_t)tb.millitm;
#else
  struct timespec ts;
  if (timespec_get(&ts, TIME_UTC) == TIME_UTC) {
    return (uint64_t)ts.tv_sec * 1000ULL + (uint64_t)(ts.tv_nsec / 1000000ULL);
  }
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (uint64_t)tv.tv_sec * 1000ULL + (uint64_t)(tv.tv_usec / 1000ULL);
#endif
}

pntr_vector null0_mouse_position() {
  pntr_vector ret = {
    .x = pntr_app_mouse_x(null0_app),
    .y = pntr_app_mouse_y(null0_app)};
  return ret;
}

pntr_vector null0_measure_image(pntr_image *image) {
  pntr_vector ret = {
    .x = image->width,
    .y = image->height};
  return ret;
}

void null0_draw_rectangle_thick_rounded(pntr_image *dst, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, int32_t thickness, pntr_color color) {
  pntr_draw_rectangle_thick_rounded(dst, x, y, width, height, cornerRadius, cornerRadius, cornerRadius, cornerRadius, thickness, color);
}

