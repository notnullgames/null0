#!/bin/bash
set -e

# this will compile a rust cart for null0

# Check if all required arguments are provided
if [ -z "${1}" ]; then
    echo "Usage: $0 CART_NAME"
    echo ""
    echo "Arguments:"
    echo "  CART_NAME  Name of the output cart (without .null0 extension)"
    exit 1
fi

CART_NAME="${1}"

echo "Compiling rust cart from /src/ to /out/"

mkdir -p "/tmp/${CART_NAME}"

# Copy all files including hidden files (like .cartignore)
cp -R /src/. "/tmp/${CART_NAME}/"
cd "/tmp/${CART_NAME}/"

# keep cargo caches writable, even when running as another user
export CARGO_HOME=/tmp/cargo

# point the null0 path-dependency at the baked-in bindings
if grep -qE '^null0\s*=\s*\{\s*path\s*=' Cargo.toml; then
    sed -i -E 's#^null0\s*=\s*\{\s*path\s*=\s*"[^"]*"#null0 = { path = "/usr/local/include/null0rust"#' Cargo.toml
else
    sed -i -E 's#^\[dependencies\]#[dependencies]\nnull0 = { path = "/usr/local/include/null0rust" }#' Cargo.toml
fi

cargo build --target wasm32-unknown-unknown --release

CRATE_NAME=$(sed -n 's/^name\s*=\s*"\(.*\)"/\1/p' Cargo.toml | head -1 | tr '-' '_')

# package only main.wasm + assets as the cart
mkdir -p "/tmp/${CART_NAME}.pkg"
cp "target/wasm32-unknown-unknown/release/${CRATE_NAME}.wasm" "/tmp/${CART_NAME}.pkg/main.wasm"
[ -d assets ] && cp -R assets "/tmp/${CART_NAME}.pkg/"

/usr/local/bin/zipcart.sh "${CART_NAME}" "/tmp/${CART_NAME}.pkg" /out
