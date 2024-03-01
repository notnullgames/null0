#!/bin/bash

CART=$1
WASM=$2
FILES_DIR=$3

cd "$(dirname ${WASM})" && \
cp "${WASM}" main.wasm && \
zip -r "${CART}" main.wasm && \
rm main.wasm

if [ ! -z "${FILES_DIR}" ];then
	cd "${FILES_DIR}"
	zip -r "${CART}" .  -x '.*' -x '__MACOSX' -x '*.c' -x '*.h'  -x '**/.*' -x '**/__MACOSX' -x '**/*.c' -x '**/*.h' -x 'README.md'
fi