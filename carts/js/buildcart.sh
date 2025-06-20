#!/bin/bash

# this will build a JS cart (zip file with quickjs main.wasm)

CART="${1}"
WASM=$(basename "${2}")
WASM_DIR=$(dirname "${2}")
FILES_DIR="${3}"

cp "${WASM_DIR}/${WASM}" "${FILES_DIR}/main.wasm"
cd "${FILES_DIR}"

zip -rq "${CART}" . -x "*.c" "*.h" ".DS_Store" "__*"

echo "Zip contents:"
unzip -l "${CART}"

rm "${FILES_DIR}/main.wasm"
