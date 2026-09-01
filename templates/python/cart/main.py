# the null0 API is available as plain globals - nothing to import at runtime.
# drop null0.pyi next to this file and open with the type-checking-only import
# below for editor completion (it never runs, and this RustPython has no
# `typing` module to import from).

TYPE_CHECKING = False

if TYPE_CHECKING:
    from null0 import *


def load():
    clear(BLUE)
    draw_circle(100, 100, 50, RED)
    draw_text(FONT_DEFAULT, 'hello from Python', 170, 92, WHITE)


# other callbacks you can define:
#
#   def update(): pass
#   def unload(): pass
#   def buttonDown(button, player): pass
