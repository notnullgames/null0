#!/bin/bash
set -e

# this will compile a go (tinygo) cart for null0

# Check if all required arguments are provided
if [ -z "${1}" ]; then
    echo "Usage: $0 CART_NAME"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    exit 1
fi

CART_NAME="${1}"

echo "Compiling go cart from /src/ to /out/"

mkdir -p "/tmp/${CART_NAME}"

# Copy all files including hidden files (like .cartignore)
cp -R /src/. "/tmp/${CART_NAME}/"
cd "/tmp/${CART_NAME}/"

# make the null0 bindings available as a local module
if [ ! -f go.mod ]; then
    go mod init cart
    go mod edit -require=null0@v0.0.0 -replace=null0=/usr/local/include/null0go
fi

export GOFLAGS=-mod=mod
export GOPROXY=off
tinygo build -target wasip1 -opt z -no-debug -o main.wasm .

# package only main.wasm + assets as the cart
mkdir -p "/tmp/${CART_NAME}.pkg"
cp main.wasm "/tmp/${CART_NAME}.pkg/"
[ -d assets ] && cp -R assets "/tmp/${CART_NAME}.pkg/"

/usr/local/bin/zipcart.sh "${CART_NAME}" "/tmp/${CART_NAME}.pkg" /out
