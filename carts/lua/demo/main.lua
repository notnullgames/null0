-- demo lua cart for null0 (interpreted, via GopherLua)
--
-- exercises more of the API than simple/: shapes, a Vector[] polygon, text,
-- and per-frame animation state. the null0 API is available as plain
-- globals - no require() needed. structs (Color/Vector/Rectangle/
-- Dimensions/SfxParams) are plain tables, e.g. {r = 0, g = 121, b = 241, a = 255}
--
-- null0.lua (in carts/lua) has definitions for every function & constant, so
-- any LuaLS-based editor can complete them for you.

local frame = 0

function update()
  frame = frame + 1

  clear(DARKGRAY)
  draw_text(FONT_DEFAULT, 'null0 demo', 20, 20, WHITE)
  draw_rectangle(40, 80, 100, 70, RED)
  draw_circle(220, 115, 45, GREEN)
  draw_triangle(320, 150, 400, 150, 360, 60, BLUE)
  draw_line(40, 250, 600, 250, LIGHTGRAY)

  -- hexagon - the Vector[] array-arg call
  local hexagon = {
    { x = 460, y = 80 },
    { x = 520, y = 80 },
    { x = 550, y = 140 },
    { x = 520, y = 200 },
    { x = 460, y = 200 },
    { x = 430, y = 140 },
  }
  draw_polygon(hexagon, PURPLE)

  -- a circle sweeping left-to-right across the bottom, proving update()
  -- is called repeatedly and state persists
  local x = frame % 600
  draw_circle(x + 20, 350, 20, YELLOW)

  draw_text(FONT_DEFAULT, 'shapes + animation + text', 20, 440, ORANGE)
end
