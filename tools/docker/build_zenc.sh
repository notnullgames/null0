#!/bin/bash
set -e

# Compile a Zen-C cart for null0

if [ -z "${1}" ]; then
    echo "Usage: $0 CART_NAME"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    exit 1
fi

CART_NAME="${1}"

echo "Compiling Zen-C cart from /src/ to /out/"

export PATH="${PATH}:/opt/wasi-sdk/bin"

mkdir -p "/tmp/${CART_NAME}"

# Copy all files including hidden files (like .cartignore)
cp -R /src/. "/tmp/${CART_NAME}/"
cd "/tmp/${CART_NAME}/"

# Make the null0 bindings available
if [ ! -f null0.zc ]; then
    cp /usr/local/include/null0.zc .
fi
if [ ! -f null0.h ]; then
    cp /usr/local/include/null0.h .
fi

# Find the main Zen-C source file (main.zc or first .zc file)
MAIN_ZC="main.zc"
if [ ! -f "$MAIN_ZC" ]; then
    MAIN_ZC=$(ls *.zc 2>/dev/null | head -1)
fi

if [ -z "$MAIN_ZC" ]; then
    echo "Error: No .zc source file found"
    exit 1
fi

echo "Transpiling ${MAIN_ZC} to C..."
zc transpile "$MAIN_ZC" -o main.c

echo "Compiling to wasm..."
clang -I . -nostartfiles \
    -Wl,--no-entry,--initial-memory=67108864,--max-memory=67108864,-z,stack-size=8388608 \
    -o main.wasm main.c

# Package only main.wasm + assets as the cart
mkdir -p "/tmp/${CART_NAME}.pkg"
cp main.wasm "/tmp/${CART_NAME}.pkg/"
[ -d assets ] && cp -R assets "/tmp/${CART_NAME}.pkg/"

/usr/local/bin/zipcart.sh "${CART_NAME}" "/tmp/${CART_NAME}.pkg" /out
