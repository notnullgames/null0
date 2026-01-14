#!/bin/bash

# this will compile a nim cart for null0

# Check if all required arguments are provided
if [ -z "${1}" ]; then
    echo "Usage: $0 CART_NAME"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    exit 1
fi

CART_NAME="${1}"

echo "Compiling Nim cart from /src/ to /out/"

mkdir -p "/tmp/${CART_NAME}"

cp -R /src/* /src/.* "/tmp/${CART_NAME}/" 2>/dev/null
cd "/tmp/${CART_NAME}/"
nim c --threads:off --noMain --cc:env -d:release -d:wasi -d:useMalloc --cpu:wasm32 --os:any --passC:"-D_WASI_EMULATED_SIGNAL" --passL:"-lwasi-emulated-signal" --passL:"-Wl,--allow-undefined" -o:main.wasm main.nim

/usr/local/bin/zipcart.sh "${CART_NAME}" "/tmp/${CART_NAME}/" /out