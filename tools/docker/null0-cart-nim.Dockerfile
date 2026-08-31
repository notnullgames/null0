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

COPY tools/docker/build_nim.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y nim && rm -rf /var/lib/apt/lists/*

COPY carts/nim/null0.nim /usr/local/include

ENTRYPOINT ["build_nim.sh"]