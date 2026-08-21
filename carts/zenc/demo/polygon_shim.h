// null0 Zen-C demo helper: zc v0.4.4 segfaults its own compiler the moment
// user code writes a declaration (local var, global, return type, or a
// user-authored extern fn parameter) that names one of null0's C-interop
// struct types (Color, Vector, Rectangle, Dimensions, SfxParams) - see the
// "no arrays" note in carts/zenc/simple/main.zc for the by-value case this
// hits too. draw_polygon needs a `Vector*` parameter, which is impossible
// to spell in zc source without tripping that crash, so this header
// re-imports the same host function ("draw_polygon" in the "null0" import
// module - matching NULL0_IMPORT("draw_polygon") in null0.h) under a
// different C name, using only plain integer/byte pointers. A Vector is
// two consecutive i32s (x, y) and a Color is 4 consecutive u8s (r, g, b,
// a), so this is layout-compatible with the real signature - it just lets
// zc's compiler avoid ever parsing the word "Vector" or "Color".
#pragma once

#define NULL0_POLY_IMPORT(n) __attribute__((import_module("null0"), import_name(n)))

NULL0_POLY_IMPORT("draw_polygon")
extern void draw_polygon_raw(i32* points, i32 numPoints, u8* color);
