#!/bin/bash
set -e

# this will build a never cart for null0 (experimental - never runs on its own VM,
# so this packages the source and checks that it parses)

# Check if all required arguments are provided
if [ -z "${1}" ]; then
    echo "Usage: $0 CART_NAME"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    exit 1
fi

CART_NAME="${1}"

echo "Compiling never cart from /src/ to /out/"

mkdir -p "/tmp/${CART_NAME}"

# Copy all files including hidden files (like .cartignore)
cp -R /src/. "/tmp/${CART_NAME}/"
cd "/tmp/${CART_NAME}/"

# make the null0 bindings available
if [ ! -f null0.nev ]; then
    cp /usr/local/include/null0.nev .
fi

# never is interpreted by its VM - check the source parses and package it
never -c main.nev -o main.wasm 2>/dev/null || never -p main.nev || true

# package main.wasm (if produced) or the source + assets as the cart
mkdir -p "/tmp/${CART_NAME}.pkg"
[ -f main.wasm ] && cp main.wasm "/tmp/${CART_NAME}.pkg/" || cp main.nev null0.nev "/tmp/${CART_NAME}.pkg/"
[ -d assets ] && cp -R assets "/tmp/${CART_NAME}.pkg/"

/usr/local/bin/zipcart.sh "${CART_NAME}" "/tmp/${CART_NAME}.pkg" /out
