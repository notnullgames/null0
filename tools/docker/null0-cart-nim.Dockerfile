# The C image is the base (wasi-sdk + zipcart + null0.h). CI overrides BASE
# with the one it just built, so this image is never assembled on top of a
# previously-published C image that predates the bindings it's baking in.
ARG BASE=ghcr.io/notnullgames/null0-cart-c:latest
FROM ${BASE}

COPY tools/docker/build_nim.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y nim && rm -rf /var/lib/apt/lists/*

COPY carts/nim/null0.nim /usr/local/include

ENTRYPOINT ["build_nim.sh"]