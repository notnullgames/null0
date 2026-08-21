#include "null0.h"

u32 map;
i32 camX = 0;
i32 camY = 0;
i32 speed = 4;

int main() {
  map = load_tilemap("assets/main.tmj");
  if (map == 0) {
    printf("failed to load tilemap\n");
    return 0;
  }
  printf("tilemap loaded: handle %u, %d layers\n", map, tile_layer_count(map));
  printf("tile at (0, 0) in layer 0: gid %d\n", tile_get_tile(map, 0, 0, 0));
  return 0;
}

void update() {
  if (key_down(KEY_LEFT)) {
    camX -= speed;
  }
  if (key_down(KEY_RIGHT)) {
    camX += speed;
  }
  if (key_down(KEY_UP)) {
    camY -= speed;
  }
  if (key_down(KEY_DOWN)) {
    camY += speed;
  }

  clear(BLACK);
  tile_update(map, delta_time());
  tile_draw(map, -camX, -camY);
}
