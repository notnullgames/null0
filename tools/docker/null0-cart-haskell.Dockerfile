FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y curl jq unzip zstd xz-utils zip ca-certificates python3 make && rm -rf /var/lib/apt/lists/*

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_haskell.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

# ghc-wasm-meta's bootstrap script installs wasm32-wasi-ghc (plus its bundled
# clang/wasi-sdk) to /root/.ghc-wasm, auto-detecting host architecture.
#
# It lays down 6.6G, most of which a cart build never touches. Pruned in the
# *same* layer as the install - deleting in a later RUN would leave the files
# in the earlier layer and shrink nothing:
#
#   doc/       853M of haddock HTML
#   *_p.a     1.1G of profiling libraries; carts build -O2, never -prof
#   wasmtime  }
#   binaryen  }  126M/166M/80M - installed for running and packaging wasm,
#   cabal     }  none of which build_haskell.sh invokes
#
# nodejs stays: GHC's wasm backend shells out to it as the external
# interpreter, so any cart using TemplateHaskell fails without it
# ("/usr/bin/env: 'node': No such file or directory").
RUN curl https://gitlab.haskell.org/haskell-wasm/ghc-wasm-meta/-/raw/master/bootstrap.sh | sh && \
    GHC_DIR=/root/.ghc-wasm/wasm32-wasi-ghc && \
    rm -rf "${GHC_DIR}/doc" && \
    find "${GHC_DIR}" -name '*_p.a' -delete && \
    rm -rf /root/.ghc-wasm/wasmtime /root/.ghc-wasm/binaryen /root/.ghc-wasm/cabal && \
    chmod -R a+rX /root
ENV PATH="/root/.ghc-wasm:${PATH}"

COPY carts/haskell/Null0.hs /usr/local/include/
COPY tools/docker/haskell-cart/imports.c /usr/local/include/

VOLUME /src
VOLUME /out
WORKDIR /src

ENTRYPOINT ["build_haskell.sh"]
