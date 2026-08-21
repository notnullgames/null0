#!/bin/bash
set -e

# this will compile a haxe cart for null0 (haxe -> HL/C -> wasi-sdk)

# Check if all required arguments are provided
if [ -z "${1}" ]; then
    echo "Usage: $0 CART_NAME"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    exit 1
fi

CART_NAME="${1}"

echo "Compiling haxe cart from /src/ to /out/"
haxe --version

mkdir -p "/tmp/${CART_NAME}"

# Copy all files including hidden files (like .cartignore)
cp -R /src/. "/tmp/${CART_NAME}/"
cd "/tmp/${CART_NAME}/"

# make the null0 bindings available if the cart doesn't ship them
if [ ! -f Null0.hx ]; then
    cp /opt/null0-haxe/Null0.hx .
fi

# haxe -> C (HL/C). haxe shells out to haxelib for the native build step,
# which is a no-op shim in this image - we do the compile ourselves.
haxe -cp . -main Main -hl out/main.c

HL=/opt/hashlink

# compile the generated C + hashlink runtime + null0 glue with wasi-sdk.
# - stubinc shadows headers wasi-libc lacks (setjmp.h, termios.h, ...)
# - hlc_main.c is shadowed by /opt/null0-haxe/hlc_main.c (cart entry)
clang -O2 \
    -I/opt/null0-haxe/stubinc -I/opt/null0-haxe -Iout -I"${HL}/src" \
    -include /opt/null0-haxe/stubinc/wasi_fixes.h \
    -D_WASI_EMULATED_MMAN -D_WASI_EMULATED_PROCESS_CLOCKS \
    -DHL_LINUX -DCLOCK_THREAD_CPUTIME_ID=CLOCK_MONOTONIC -w \
    -o main.wasm \
    out/main.c \
    /opt/null0-haxe/null0_shim.c \
    /opt/null0-haxe/stubs.c \
    "${HL}/src/gc.c" \
    "${HL}/src/std/array.c" \
    "${HL}/src/std/buffer.c" \
    "${HL}/src/std/bytes.c" \
    "${HL}/src/std/cast.c" \
    "${HL}/src/std/date.c" \
    "${HL}/src/std/error.c" \
    "${HL}/src/std/file.c" \
    "${HL}/src/std/fun.c" \
    "${HL}/src/std/maps.c" \
    "${HL}/src/std/math.c" \
    "${HL}/src/std/obj.c" \
    "${HL}/src/std/random.c" \
    "${HL}/src/std/string.c" \
    "${HL}/src/std/sys.c" \
    "${HL}/src/std/thread.c" \
    "${HL}/src/std/track.c" \
    "${HL}/src/std/types.c" \
    "${HL}/src/std/ucs2.c" \
    -lwasi-emulated-mman -lwasi-emulated-process-clocks \
    -Wl,--initial-memory=67108864,--max-memory=67108864,-z,stack-size=8388608 \
    -Wl,--export=malloc -Wl,--export=free

# package only main.wasm + assets as the cart
mkdir -p "/tmp/${CART_NAME}.pkg"
cp main.wasm "/tmp/${CART_NAME}.pkg/"
[ -d assets ] && cp -R assets "/tmp/${CART_NAME}.pkg/"

/usr/local/bin/zipcart.sh "${CART_NAME}" "/tmp/${CART_NAME}.pkg" /out
