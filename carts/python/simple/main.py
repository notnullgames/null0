# simple python cart for null0 (interpreted, via RustPython)
#
# the null0 API is available as plain globals - no import needed, same as
# the JS carts. structs (Color/Vector/Rectangle/Dimensions/SfxParams) are
# plain dicts, e.g. {'r':.., 'g':.., 'b':.., 'a':..}

counter = 0


def load():
    print('python cart says "hi"')
    print('Press buttons to see reaction.')
    print('Press SPACE to see text on screen.')


def buttonDown(button, player):
    print('buttonDown:', button, player)


def update():
    global counter
    counter += 1
    clear(BLUE)
    draw_rectangle(10, 10, 100, 50, RED)
    if key_down(KEY_SPACE):
        draw_text(FONT_DEFAULT, 'Space pressed!', 50, 50, WHITE)

# other callbacks you can implement:
# def unload(): pass
# def buttonUp(button, player): pass
# def keyUp(key): pass
# def keyDown(key): pass
# def mouseDown(button): pass
# def mouseUp(button): pass
# def mouseMoved(x, y): pass
