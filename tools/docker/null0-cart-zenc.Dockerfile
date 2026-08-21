FROM ghcr.io/webassembly/wasi-sdk:latest

ARG ZENC_VERSION=0.4.4

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_zenc.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y git make build-essential zip && rm -rf /var/lib/apt/lists/*

# Build Zen-C compiler from source (use system gcc, not wasi-sdk clang)
RUN git clone --depth 1 --branch "v${ZENC_VERSION}" https://github.com/zenc-lang/zenc.git /opt/zenc-src && \
    cd /opt/zenc-src && \
    make clean && \
    CC=gcc make && \
    make install && \
    cd / && rm -rf /opt/zenc-src

VOLUME /src
VOLUME /out
WORKDIR /src

ENV PATH="/opt/wasi-sdk/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
ENV WASI_SDK_DIR="/opt/wasi-sdk"

COPY carts/zenc/null0.h /usr/local/include/

ENTRYPOINT ["build_zenc.sh"]
