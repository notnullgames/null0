# simple python cart for null0 (built with py2wasm)
#
# NOTE: py2wasm cannot yet declare custom host imports, so the null0
# calls below raise NotImplementedError at runtime. This example shows
# how a cart would look once a null0-aware Python runtime exists.

import null0


def load():
    null0.clear(null0.BLUE)
    null0.draw_circle(100, 100, 50, null0.RED)


def update():
    pass


# other callbacks you can implement:
# def unload():
#     pass
# def buttonUp(button: int, player: int):
#     pass
# def buttonDown(button: int, player: int):
#     pass
# def keyUp(key: int):
#     pass
# def keyDown(key: int):
#     pass
# def mouseDown(button: int):
#     pass
# def mouseUp(button: int):
#     pass
# def mouseMoved(x: float, y: float):
#     pass


if __name__ == "__main__":
    load()
