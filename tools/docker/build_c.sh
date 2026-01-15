#!/bin/bash

# this will compile a C cart for null0

# Check if all required arguments are provided
if [ -z "${1}" ]; then
    echo "Usage: $0 CART_NAME"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    exit 1
fi

CART_NAME="${1}"

export PATH="${PATH}:/opt/wasi-sdk/bin"

echo "Compiling C cart from /src/ to /out/"
clang --version

mkdir -p "/tmp/${CART_NAME}"

# Copy all files including hidden files (like .cartignore)
cp -R /src/. "/tmp/${CART_NAME}/"
cd "/tmp/${CART_NAME}/"
clang -I /usr/local/include/ -Wl,--initial-memory=67108864,--max-memory=67108864,-z,stack-size=8388608 -o main.wasm main.c 

/usr/local/bin/zipcart.sh "${CART_NAME}" "/tmp/${CART_NAME}/" /out