#!/bin/bash
set -e

# this will compile a haskell cart for null0

source /root/.ghc-wasm/env

# Check if all required arguments are provided
if [ -z "${1}" ]; then
    echo "Usage: $0 CART_NAME"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    exit 1
fi

CART_NAME="${1}"

echo "Compiling haskell cart from /src/ to /out/"

mkdir -p "/tmp/${CART_NAME}"

# Copy all files including hidden files (like .cartignore)
cp -R /src/. "/tmp/${CART_NAME}/"
cd "/tmp/${CART_NAME}/"

# make the null0 bindings available to `import Null0`
if [ ! -f Null0.hs ]; then
    cp /usr/local/include/Null0.hs .
fi
if [ ! -f imports.c ]; then
    cp /usr/local/include/imports.c .
fi

# arbitrary --user UIDs have no writable $HOME, so point ghc's cache at /tmp
export XDG_CACHE_HOME="/tmp/ghc-cache"

# every `foreign export ccall "name"` in the cart's own source becomes a
# wasm export - wasm-ld strips anything not explicitly kept, so build the
# --export flags from whatever the cart actually defines (skip commented-out
# lines; `-Wl,` splits on commas, so each export needs its own --export=)
EXPORTS=$(grep -hvE '^\s*--' *.hs | grep -hoE 'foreign export ccall "[a-zA-Z0-9_]+"' | sed -E 's/.*"(.+)"/--export=\1/' | sort -u | paste -sd, -)

if [ -z "$EXPORTS" ]; then
    echo "error: no 'foreign export ccall \"name\"' declarations found in cart source"
    exit 1
fi

# -O2 matters here beyond speed: an unoptimized build pulls in enough extra
# RTS/base code that WAMR's fixed internal pool runs out of room during
# instantiation ("failed to allocate memory for gc object") on anything
# past a trivial cart
wasm32-wasi-ghc -c imports.c -o imports.o
wasm32-wasi-ghc -O2 *.hs imports.o -o main.wasm -no-hs-main \
    -optl-mexec-model=reactor \
    -optl-Wl,"${EXPORTS}"

# package only main.wasm + assets as the cart
mkdir -p "/tmp/${CART_NAME}.pkg"
cp main.wasm "/tmp/${CART_NAME}.pkg/"
[ -d assets ] && cp -R assets "/tmp/${CART_NAME}.pkg/"

/usr/local/bin/zipcart.sh "${CART_NAME}" "/tmp/${CART_NAME}.pkg" /out
