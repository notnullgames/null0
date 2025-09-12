#!/bin/bash

# Build script for null0 Rust cart
# This script builds the Rust project for WebAssembly

set -e

echo "Building Rust cart for null0..."

# Check if wasm32-unknown-unknown target is installed
if ! rustup target list --installed | grep -q "wasm32-unknown-unknown"; then
    echo "Installing wasm32-unknown-unknown target..."
    rustup target add wasm32-unknown-unknown
fi

# Build in release mode for optimal size
echo "Building for WebAssembly..."
cargo build --target wasm32-unknown-unknown --release

# Copy the output to a convenient location
WASM_FILE="target/wasm32-unknown-unknown/release/simple.wasm"
OUTPUT_FILE="simple.wasm"

if [ -f "$WASM_FILE" ]; then
    cp "$WASM_FILE" "$OUTPUT_FILE"
    echo "✅ Build successful! Output: $OUTPUT_FILE"
    echo "📦 File size: $(du -h $OUTPUT_FILE | cut -f1)"
else
    echo "❌ Build failed - WASM file not found"
    exit 1
fi
