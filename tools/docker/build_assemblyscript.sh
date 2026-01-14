#!/bin/bash

# this will compile an assemblyscript cart for null0

# Check if all required arguments are provided
if [ -z "${1}" ]; then
    echo "Usage: $0 CART_NAME"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    exit 1
fi

CART_NAME="${1}"

echo "Compiling Assemblyscript cart from /src/ to /out/"

mkdir -p "/tmp/${CART_NAME}"

cp -R /src/* /src/.* "/tmp/${CART_NAME}/" 2>/dev/null
cd "/tmp/${CART_NAME}/"
asc --lib /usr/local/include --optimize -o main.wasm main.ts

/usr/local/bin/zipcart.sh "${CART_NAME}" "/tmp/${CART_NAME}/" /out


