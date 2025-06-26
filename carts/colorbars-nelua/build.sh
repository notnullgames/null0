#!/bin/bash

# Build script for Nelua cart for null0 engine
# This compiles the Nelua code to C, then to WebAssembly

set -e

CART_NAME="colorbars-nelua"
OUTPUT_DIR="."
WASI_SDK_PATH="${WASI_SDK_PATH:-/opt/wasi-sdk}"

# Check if WASI SDK is available
if [ ! -d "$WASI_SDK_PATH" ]; then
    echo "Error: WASI SDK not found at $WASI_SDK_PATH"
    echo "Please install WASI SDK or set WASI_SDK_PATH environment variable"
    exit 1
fi

# Check if nelua is available
if ! command -v nelua &> /dev/null; then
    echo "Error: nelua compiler not found"
    echo "Please install Nelua: https://nelua.io/installing/"
    exit 1
fi

echo "Building $CART_NAME..."

# Set up WASI environment
export CC="$WASI_SDK_PATH/bin/clang"
export AR="$WASI_SDK_PATH/bin/llvm-ar"
export RANLIB="$WASI_SDK_PATH/bin/llvm-ranlib"

# Compile Nelua to WebAssembly
nelua \
    --cc="$CC" \
    --cflags="--target=wasm32-wasi -nostdlib -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined" \
    --cache-dir=".cache" \
    --output="$OUTPUT_DIR/$CART_NAME.wasm" \
    main.nelua

echo "Build complete: $CART_NAME.wasm"
echo "File size: $(du -h "$OUTPUT_DIR/$CART_NAME.wasm" | cut -f1)" 