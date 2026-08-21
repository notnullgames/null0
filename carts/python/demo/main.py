# demo python cart for null0 (interpreted, via RustPython)
#
# exercises more of the API than simple/: shapes, text, a polygon (list of
# dicts) and a persistent frame counter that animates a circle

frame = 0


def update():
    global frame

    clear(DARKGRAY)
    draw_text(FONT_DEFAULT, 'null0 demo', 20, 20, WHITE)

    draw_rectangle(40, 80, 100, 70, RED)
    draw_circle(220, 115, 45, GREEN)
    draw_triangle(320, 150, 400, 150, 360, 60, BLUE)
    draw_line(40, 250, 600, 250, LIGHTGRAY)

    # hexagon - a list of Vector dicts
    hexagon = [
        {'x': 460, 'y': 80},
        {'x': 520, 'y': 80},
        {'x': 550, 'y': 140},
        {'x': 520, 'y': 200},
        {'x': 460, 'y': 200},
        {'x': 430, 'y': 140},
    ]
    draw_polygon(hexagon, PURPLE)

    frame += 1
    x = frame % 600
    draw_circle(x + 20, 350, 20, YELLOW)

    draw_text(FONT_DEFAULT, 'shapes + animation + text', 20, 440, ORANGE)

# other callbacks you can implement:
# def load(): pass
# def unload(): pass
# def buttonUp(button, player): pass
# def buttonDown(button, player): pass
# def keyUp(key): pass
# def keyDown(key): pass
# def mouseDown(button): pass
# def mouseUp(button): pass
# def mouseMoved(x, y): pass
