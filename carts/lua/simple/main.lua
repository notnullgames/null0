-- simple lua cart for null0 (interpreted, via GopherLua)
--
-- the null0 API is available as plain globals - no require() needed, same as
-- the JS carts. structs (Color/Vector/Rectangle/Dimensions/SfxParams) are
-- plain tables, e.g. {r = 0, g = 121, b = 241, a = 255}
--
-- null0.lua (in carts/lua) has definitions for every function & constant, so
-- any LuaLS-based editor can complete them for you.

local counter = 0

function load()
  print('lua cart says "hi"')
  print('Press buttons to see reaction.')
  print('Press SPACE to see text on screen.')
end

function buttonDown(button, player)
  print('buttonDown:', button, player)
end

function update()
  counter = counter + 1
  clear(BLUE)
  draw_rectangle(10, 10, 100, 50, RED)
  if key_down(KEY_SPACE) then
    draw_text(FONT_DEFAULT, 'Space pressed!', 50, 50, WHITE)
  end
end

-- other callbacks you can implement:
-- function unload() end
-- function buttonUp(button, player) end
-- function keyUp(key) end
-- function keyDown(key) end
-- function mouseDown(button) end
-- function mouseUp(button) end
-- function mouseMoved(x, y) end
