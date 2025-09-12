#!/bin/bash

# usage ./build.sh <CART_NAME>

DIR=$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")
CART_DIR="${DIR}/${1}"
TMP_DIR="${DIR}/../../build/carts/${1}_as_tmp"

mkdir -p "${TMP_DIR}"
cd "${CART_DIR}"
npx -y asc main.ts --target release -o "${TMP_DIR}/main.wasm" --textFile "${TMP_DIR}/../${1}_as.wat" --runtime stub
cp -R "${CART_DIR}/*" "${TMP_DIR}/"
cd "${TMP_DIR}"
zip -r "../${1}_as.null0" . -x "*.ts" ".DS_Store"
