FROM konsumer/null0-cart-c:latest

ARG WREN_VERSION=0.4.0

COPY tools/docker/build_wren.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

COPY carts/c/null0.h /usr/local/include/
COPY tools/docker/wren-cart.c /tmp/wren-cart.c

ADD https://github.com/wren-lang/wren/archive/refs/tags/${WREN_VERSION}.tar.gz /tmp/wren.tar.gz

# build the interpreter (wren VM + null0 bindings) once, bake it into the image
RUN cd /tmp && tar -xzf wren.tar.gz && \
  clang -O2 \
    -I /usr/local/include \
    -I /tmp/wren-${WREN_VERSION}/src/include \
    -I /tmp/wren-${WREN_VERSION}/src/vm \
    -I /tmp/wren-${WREN_VERSION}/src/optional \
    -D_WASI_EMULATED_SIGNAL -D_WASI_EMULATED_PROCESS_CLOCKS \
    -Wl,--initial-memory=67108864,--max-memory=67108864,-z,stack-size=8388608 \
    -o /usr/local/lib/main.wasm \
    /tmp/wren-cart.c \
    /tmp/wren-${WREN_VERSION}/src/vm/*.c \
    /tmp/wren-${WREN_VERSION}/src/optional/*.c \
    -lwasi-emulated-signal -lwasi-emulated-process-clocks && \
  rm -rf /tmp/wren-${WREN_VERSION} /tmp/wren.tar.gz /tmp/wren-cart.c

VOLUME /src
VOLUME /out
WORKDIR /src

ENTRYPOINT ["build_wren.sh"]
