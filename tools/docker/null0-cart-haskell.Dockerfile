FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y curl jq unzip zstd xz-utils zip ca-certificates python3 make && rm -rf /var/lib/apt/lists/*

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_haskell.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

# ghc-wasm-meta's bootstrap script installs wasm32-wasi-ghc (plus its bundled
# clang/wasi-sdk) to /root/.ghc-wasm, auto-detecting host architecture
RUN curl https://gitlab.haskell.org/haskell-wasm/ghc-wasm-meta/-/raw/master/bootstrap.sh | sh && \
    chmod -R a+rX /root
ENV PATH="/root/.ghc-wasm:${PATH}"

COPY carts/haskell/Null0.hs /usr/local/include/
COPY tools/docker/haskell-cart/imports.c /usr/local/include/

VOLUME /src
VOLUME /out
WORKDIR /src

ENTRYPOINT ["build_haskell.sh"]
