use null0

-- persistent frame counter, incremented once per update()
global frame i32 = 0

fn update():
    null0.clear(null0.DARKGRAY)
    null0.draw_text(null0.FONT_DEFAULT, 'null0 demo', 20, 20, null0.WHITE)
    null0.draw_rectangle(40, 80, 100, 70, null0.RED)
    null0.draw_circle(220, 115, 45, null0.GREEN)
    null0.draw_triangle(320, 150, 400, 150, 360, 60, null0.BLUE)
    null0.draw_line(40, 250, 600, 250, null0.LIGHTGRAY)
    null0.draw_polygon([]null0.Vector{
        null0.Vector{x=460, y=80},
        null0.Vector{x=520, y=80},
        null0.Vector{x=550, y=140},
        null0.Vector{x=520, y=200},
        null0.Vector{x=460, y=200},
        null0.Vector{x=430, y=140},
    }, null0.PURPLE)

    frame = frame + 1
    var x i32 = frame % 600
    null0.draw_circle(x + 20, 350, 20, null0.YELLOW)

    null0.draw_text(null0.FONT_DEFAULT, 'shapes + animation + text', 20, 440, null0.ORANGE)

-- callbacks (optional - implement as needed)

-- fn load():
--     pass

-- fn unload():
--     pass

-- fn buttonUp(button int, player int):
--     pass

-- fn buttonDown(button int, player int):
--     pass

-- fn keyUp(key int):
--     pass

-- fn keyDown(key int):
--     pass

-- fn mouseDown(button int):
--     pass

-- fn mouseUp(button int):
--     pass

-- fn mouseMoved(x float, y float):
--     pass
