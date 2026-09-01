-- the null0 API is available as plain globals - no require() needed.
-- null0.lua (in carts/lua) has LuaLS definitions for editor completion.

function load()
  clear(BLUE)
  draw_circle(100, 100, 50, RED)
  draw_text(FONT_DEFAULT, 'hello from Lua', 170, 92, WHITE)
end

-- other callbacks you can implement:
--
--   function update() end
--   function unload() end
--   function buttonDown(button, player) end
