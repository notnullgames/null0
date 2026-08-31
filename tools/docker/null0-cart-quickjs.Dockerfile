# The C image is the base (wasi-sdk + zipcart + null0.h). CI overrides BASE
# with the one it just built, so this image is never assembled on top of a
# previously-published C image that predates the bindings it's baking in.
ARG BASE=ghcr.io/notnullgames/null0-cart-c:latest
FROM ${BASE}

COPY tools/docker/build_quickjs.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

ADD https://github.com/quickjs-ng/quickjs/archive/refs/heads/master.zip /tmp/quickjs-ng.zip
RUN cd /tmp/ && unzip quickjs-ng.zip
COPY tools/docker/quickjs-cart.c /tmp/quickjs-master/qjs.c

# build cart wasm & wipe source
RUN cd /tmp/quickjs-master && \
  cmake -B build     -DCMAKE_TOOLCHAIN_FILE=/opt/wasi-sdk/share/cmake/wasi-sdk-p1.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DQJS_BUILD_EXAMPLES=OFF \
    -DCMAKE_C_FLAGS="-I/usr/local/include" \
    -DCMAKE_EXE_LINKER_FLAGS="-Wl,--initial-memory=67108864,--max-memory=67108864,-z,stack-size=8388608" && \
  cmake --build build --target qjs_exe && \
  mv build/qjs /usr/local/lib/main.wasm && \
  rm -rf /tmp/quickjs-master /tmp/quickjs-ng.zip

ENTRYPOINT ["build_quickjs.sh"]