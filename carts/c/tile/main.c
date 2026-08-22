#include "null0.h"

u32 map;
i32 camX = 0;
i32 camY = 0;
i32 speed = 4;
i32 objectLayer = -1;

// what the cart spawned from the map's object layer - the map holds the
// initial state, the cart owns these
typedef struct {
  i32 gid;
  f32 x;
  f32 y;
  i32 hp;
} Entity;

Entity entities[32];
i32 entityCount = 0;

void printProp(const char* label, TilemapProp* prop) {
  switch (prop->type) {
    case PROP_INT: printf("%s %s = %d (int)\n", label, prop->name, prop->integer); break;
    case PROP_BOOL: printf("%s %s = %s (bool)\n", label, prop->name, prop->integer ? "true" : "false"); break;
    case PROP_FLOAT: printf("%s %s = %f (float)\n", label, prop->name, prop->number); break;
    case PROP_STRING: printf("%s %s = \"%s\" (string)\n", label, prop->name, prop->text); break;
    case PROP_COLOR: printf("%s %s = %08x (color)\n", label, prop->name, prop->integer); break;
    case PROP_NONE: printf("%s (no property)\n", label); break;
  }
}

int main() {
  map = load_tilemap("assets/main.tmj");
  if (map == 0) {
    printf("failed to load tilemap\n");
    fflush(stdout);
    return 0;
  }

  Dimensions* mapSize = tile_map_size(map);
  Dimensions* tileSize = tile_tile_size(map);
  printf("map: %dx%d tiles of %dx%d px, %d props\n", mapSize->width, mapSize->height, tileSize->width, tileSize->height, tile_map_prop_count(map));

  for (i32 i = 0; i < tile_layer_count(map); i++) {
    Dimensions* size = tile_layer_size(map, i);
    printf("layer %d: \"%s\" type=%d visible=%d %dx%d props=%d\n", i, tile_layer_name(map, i), tile_layer_type(map, i), tile_layer_visible(map, i), size->width, size->height, tile_layer_prop_count(map, i));
    if (tile_layer_type(map, i) == LAYER_OBJECT) {
      objectLayer = i;
    }
  }

  // spawn our own entities from the object layer's markers
  i32 count = tile_object_count(map, objectLayer);
  printf("object layer %d has %d objects\n", objectLayer, count);
  for (i32 i = 0; i < count && entityCount < 32; i++) {
    TilemapObject* object = tile_object(map, objectLayer, i);
    printf("object %d: id=%d \"%s\" type=\"%s\" gid=%d at (%f, %f) %fx%f\n", i, object->id, object->name, object->type, object->gid, object->x, object->y, object->width, object->height);
    for (i32 p = 0; p < tile_object_prop_count(map, objectLayer, i); p++) {
      printProp("  prop:", tile_object_prop_at(map, objectLayer, i, p));
    }
    entities[entityCount].gid = object->gid;
    entities[entityCount].x = object->x;
    entities[entityCount].y = object->y - object->height;
    entities[entityCount].hp = tile_object_prop(map, objectLayer, i, "hp")->integer;
    entityCount++;
  }

  // by-name lookups
  i32 grass = tile_layer_index(map, "grass");
  i32 heart = tile_object_index(map, objectLayer, "heart");
  printf("layer \"grass\" is %d, object \"heart\" is %d\n", grass, heart);
  printProp("tile 92:", tile_gid_prop(map, 92, "kind"));
  printProp("missing:", tile_layer_prop(map, 0, "nope"));

  printf("arrows scroll, S swaps a tile\n");
  fflush(stdout);
  return 0;
}

void update() {
  if (key_down(KEY_LEFT)) camX -= speed;
  if (key_down(KEY_RIGHT)) camX += speed;
  if (key_down(KEY_UP)) camY -= speed;
  if (key_down(KEY_DOWN)) camY += speed;

  // a changed gid is how the map keeps its own state
  if (key_pressed(KEY_S)) {
    i32 gid = tile_get_tile(map, 0, 2, 2);
    tile_set_tile(map, 0, 2, 2, gid == 92 ? 93 : 92);
    printf("tile (2,2): %d -> %d\n", gid, tile_get_tile(map, 0, 2, 2));
    fflush(stdout);
  }

  clear(BLACK);
  tile_update(map, delta_time());

  // draw the map's own layers, but never the object layer
  for (i32 i = 0; i < tile_layer_count(map); i++) {
    if (i != objectLayer && tile_layer_type(map, i) != LAYER_GROUP) {
      tile_draw_layer(map, i, -camX, -camY);
    }
  }

  // ...and draw our entities ourselves
  for (i32 i = 0; i < entityCount; i++) {
    tile_draw_tile(map, entities[i].gid, (i32)entities[i].x - camX, (i32)entities[i].y - camY);
  }
}
