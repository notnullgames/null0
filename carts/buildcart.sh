#!/bin/bash

# This will build a cart (zip file with main.wasm)

# buildcart.sh "fullpath/to/whatever.null0" "fullpath/to/whatever.wasm" "fullpath/to/assets"

CART="${1}"
WASM=$(basename "${2}")
WASM_DIR=$(dirname "${2}")
FILES_DIR="${3}"

cp "${WASM_DIR}/${WASM}" "${FILES_DIR}/main.wasm"
cd "${FILES_DIR}"

shopt -s extglob
zip -rq "${CART}" main.wasm **/!(*.c|*.h|.DS_Store|__*)
shopt -u extglob

rm "${FILES_DIR}/main.wasm"