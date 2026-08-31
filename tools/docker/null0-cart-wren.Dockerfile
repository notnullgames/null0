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
