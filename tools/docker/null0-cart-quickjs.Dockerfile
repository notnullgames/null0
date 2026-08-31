# Self-contained on purpose. This used to be `FROM konsumer/null0-cart-c`,
# which meant it baked whatever null0.h the *last published* C image had - the
# same staleness that silently broke haxe carts. Building on the wasi-sdk
# directly keeps every image independent, so CI can build each one and its
# carts in the same job with nothing to order.
FROM ghcr.io/webassembly/wasi-sdk:latest

COPY tools/docker/zipcart.sh /usr/local/bin/
RUN apt-get update && apt-get install -y zip && rm -rf /var/lib/apt/lists/*

VOLUME /src
VOLUME /out
WORKDIR /src

ENV PATH="/opt/wasi-sdk/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
ENV CC="/opt/wasi-sdk/bin/clang"
ENV CXX="/opt/wasi-sdk/bin/clang++"
ENV LD="/opt/wasi-sdk/bin/wasm-ld"
ENV AR="/opt/wasi-sdk/bin/llvm-ar"
ENV WASI_SDK_DIR="/opt/wasi-sdk"

COPY carts/c/null0.h /usr/local/include/

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