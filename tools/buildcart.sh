#!/bin/bash

# this will build a single cart

shopt -s extglob

CART=$1
WASM=$2
FILES_DIR=$3

cd "$(dirname ${WASM})" && \
cp "${WASM}" main.wasm && \
zip -r "${CART}" main.wasm && \
rm main.wasm

if [ ! -z "${FILES_DIR}" ];then
	cd "${FILES_DIR}"
	zip -r "${CART}" **/!(*.c|*.h|.DS_Store|__*)
fi

shopt -u extglob