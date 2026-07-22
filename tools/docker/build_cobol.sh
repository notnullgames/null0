#!/bin/bash
set -e

# this will compile a COBOL cart for null0 (gnucobol -> C -> standalone wasm, via cobweb)

# Check if all required arguments are provided
if [ -z "${1}" ]; then
    echo "Usage: $0 CART_NAME"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    exit 1
fi

CART_NAME="${1}"

echo "Compiling COBOL cart from /src/ to /out/"

source /opt/cobweb/deps/emsdk/emsdk_env.sh > /dev/null

mkdir -p "/tmp/${CART_NAME}"

# Copy all files including hidden files (like .cartignore)
cp -R /src/. "/tmp/${CART_NAME}/"
cd "/tmp/${CART_NAME}/"

# translate COBOL to C (static calls, so no runtime symbol-resolution)
cobc -C -x -static -free -I /usr/local/include main.cob -o main.c

# compile with the cobweb toolchain; the shim maps the calls to null0 host-imports
emcc -O2 main.c /usr/local/include/null0_cobol_shim.c \
  -I /opt/cobweb/dist/include \
  -L /opt/cobweb/dist/lib -lcob -lgmp \
  -s STANDALONE_WASM=1 \
  -s ERROR_ON_UNDEFINED_SYMBOLS=0 \
  -Wl,--initial-memory=67108864,--max-memory=67108864,-z,stack-size=8388608 \
  -o main.wasm

# package only main.wasm + assets as the cart
mkdir -p "/tmp/${CART_NAME}.pkg"
cp main.wasm "/tmp/${CART_NAME}.pkg/"
[ -d assets ] && cp -R assets "/tmp/${CART_NAME}.pkg/"

/usr/local/bin/zipcart.sh "${CART_NAME}" "/tmp/${CART_NAME}.pkg" /out
