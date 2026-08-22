-- the map holds the initial state; this cart owns whatever it spawns from it

local map
local camX, camY = 0, 0
local speed = 4
local objectLayer = -1
local entities = {}

local function propString(prop)
  if prop.type == PROP_INT then return string.format('%s = %d (int)', prop.name, prop.integer) end
  if prop.type == PROP_BOOL then return string.format('%s = %s (bool)', prop.name, prop.integer ~= 0) end
  if prop.type == PROP_FLOAT then return string.format('%s = %f (float)', prop.name, prop.number) end
  if prop.type == PROP_STRING then return string.format('%s = "%s" (string)', prop.name, prop.text) end
  if prop.type == PROP_COLOR then return string.format('%s = %08x (color)', prop.name, prop.integer) end
  return '(no property)'
end

function load()
  map = load_tilemap('assets/main.tmj')
  if map == 0 then
    print('failed to load tilemap')
    return
  end

  local size = tile_map_size(map)
  local tileSize = tile_tile_size(map)
  print(string.format('map: %dx%d tiles of %dx%d px, %d props', size.width, size.height, tileSize.width, tileSize.height, tile_map_prop_count(map)))

  for i = 0, tile_layer_count(map) - 1 do
    local layerSize = tile_layer_size(map, i)
    print(string.format('layer %d: "%s" type=%d visible=%s %dx%d props=%d', i, tile_layer_name(map, i), tile_layer_type(map, i), tostring(tile_layer_visible(map, i)), layerSize.width, layerSize.height, tile_layer_prop_count(map, i)))
    if tile_layer_type(map, i) == LAYER_OBJECT then
      objectLayer = i
    end
  end

  local count = tile_object_count(map, objectLayer)
  print(string.format('object layer %d has %d objects', objectLayer, count))
  for i = 0, count - 1 do
    local object = tile_object(map, objectLayer, i)
    print(string.format('object %d: id=%d "%s" type="%s" gid=%d at (%f, %f) %fx%f', i, object.id, object.name, object.type, object.gid, object.x, object.y, object.width, object.height))
    for p = 0, tile_object_prop_count(map, objectLayer, i) - 1 do
      print('  prop: ' .. propString(tile_object_prop_at(map, objectLayer, i, p)))
    end
    entities[#entities + 1] = {
      gid = object.gid,
      x = object.x,
      y = object.y - object.height,
      hp = tile_object_prop(map, objectLayer, i, 'hp').integer
    }
  end

  print(string.format('layer "grass" is %d, object "heart" is %d', tile_layer_index(map, 'grass'), tile_object_index(map, objectLayer, 'heart')))
  print('tile 92: ' .. propString(tile_gid_prop(map, 92, 'kind')))
  print('missing: ' .. propString(tile_layer_prop(map, 0, 'nope')))
end

function update()
  if key_down(KEY_LEFT) then camX = camX - speed end
  if key_down(KEY_RIGHT) then camX = camX + speed end
  if key_down(KEY_UP) then camY = camY - speed end
  if key_down(KEY_DOWN) then camY = camY + speed end

  -- a changed gid is how the map keeps its own state
  if key_pressed(KEY_S) then
    local gid = tile_get_tile(map, 0, 2, 2)
    tile_set_tile(map, 0, 2, 2, gid == 92 and 93 or 92)
    print(string.format('tile (2,2): %d -> %d', gid, tile_get_tile(map, 0, 2, 2)))
  end

  clear(BLACK)
  tile_update(map, delta_time())

  for i = 0, tile_layer_count(map) - 1 do
    if i ~= objectLayer and tile_layer_type(map, i) ~= LAYER_GROUP then
      tile_draw_layer(map, i, -camX, -camY)
    end
  end

  for _, entity in ipairs(entities) do
    tile_draw_tile(map, entity.gid, entity.x - camX, entity.y - camY)
  end
end
