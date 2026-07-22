#!/bin/bash
set -e

# this will build a wisp cart for null0 (experimental - wisp cannot import
# host functions yet, so this packages the source)

# Check if all required arguments are provided
if [ -z "${1}" ]; then
    echo "Usage: $0 CART_NAME"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    exit 1
fi

CART_NAME="${1}"

echo "Compiling wisp cart from /src/ to /out/"

mkdir -p "/tmp/${CART_NAME}"

# Copy all files including hidden files (like .cartignore)
cp -R /src/. "/tmp/${CART_NAME}/"
cd "/tmp/${CART_NAME}/"

# make the null0 bindings available
if [ ! -f null0.wisp ]; then
    cp /usr/local/include/null0.wisp .
fi

# package the source + assets as the cart (wisp carts are source-level for now)
mkdir -p "/tmp/${CART_NAME}.pkg"
cp main.wisp null0.wisp "/tmp/${CART_NAME}.pkg/"
[ -d assets ] && cp -R assets "/tmp/${CART_NAME}.pkg/"

/usr/local/bin/zipcart.sh "${CART_NAME}" "/tmp/${CART_NAME}.pkg" /out
