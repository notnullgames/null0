#!/bin/bash
set -e

# this will compile a D cart for null0

# Check if all required arguments are provided
if [ -z "${1}" ]; then
    echo "Usage: $0 CART_NAME"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    exit 1
fi

CART_NAME="${1}"

echo "Compiling D cart from /src/ to /out/"

mkdir -p "/tmp/${CART_NAME}"

# Copy all files including hidden files (like .cartignore)
cp -R /src/. "/tmp/${CART_NAME}/"
cd "/tmp/${CART_NAME}/"

# make the null0 bindings available to `import null0`
if [ ! -f null0.d ]; then
    cp /usr/local/include/null0.d .
fi

ldc2 -mtriple=wasm32-unknown-unknown-wasm -betterC -Oz \
    -L--no-entry -L--export-dynamic -L--allow-undefined \
    -of=main.wasm main.d null0.d
rm -f main.o

# package only main.wasm + assets as the cart
mkdir -p "/tmp/${CART_NAME}.pkg"
cp main.wasm "/tmp/${CART_NAME}.pkg/"
[ -d assets ] && cp -R assets "/tmp/${CART_NAME}.pkg/"

/usr/local/bin/zipcart.sh "${CART_NAME}" "/tmp/${CART_NAME}.pkg" /out
