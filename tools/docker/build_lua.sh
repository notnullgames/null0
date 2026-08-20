#!/bin/bash
set -e

# this will assemble a lua cart for null0 (interpreted, via a baked-in GopherLua main.wasm)

# Check if all required arguments are provided
if [ -z "${1}" ]; then
    echo "Usage: $0 CART_NAME"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    exit 1
fi

CART_NAME="${1}"

echo "Compiling lua cart from /src/ to /out/"

mkdir -p "/tmp/${CART_NAME}"

# Copy all files including hidden files (like .cartignore)
cp -R /src/. "/tmp/${CART_NAME}/"
cp /usr/local/lib/main.wasm "/tmp/${CART_NAME}/"

# null0.lua is only LuaLS definitions (for editors), no need to ship it
rm -f "/tmp/${CART_NAME}/null0.lua"

/usr/local/bin/zipcart.sh "${CART_NAME}" "/tmp/${CART_NAME}/" /out
