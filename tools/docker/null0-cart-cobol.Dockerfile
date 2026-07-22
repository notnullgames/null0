FROM --platform=linux/amd64 ubuntu:18.04

SHELL ["/bin/bash", "-c"]

RUN apt-get update && \
    apt-get -y install git gcc libgmp-dev make python3 python3-distutils autoconf texinfo zip curl patch ca-certificates bison flex help2man && \
    rm -rf /var/lib/apt/lists/*

# cobweb toolchain (GnuCOBOL 2.2 + emscripten), following cloudflare/cobweb's Dockerfile
# (the vendored gnucobol-2.2 tree already has cobweb's libcob patches applied)
ARG COBWEB_COMMIT=28aed919ce2d7471084bd7ef22b2fe1f232b3b78
RUN git clone https://github.com/cloudflare/cobweb.git /opt/cobweb && \
    cd /opt/cobweb && git checkout ${COBWEB_COMMIT}

# install cobc (for cobol -> C translation)
RUN cd /opt/cobweb/deps/gnucobol-2.2 && \
    ./configure --without-db --prefix=/usr/ && \
    make && make install && make clean

# install emscripten (the vendored emsdk pins an old, 18.04-compatible version)
RUN cd /opt/cobweb/deps/emsdk && ./emsdk install latest && ./emsdk activate latest

ENV PATH="/opt/cobweb/deps/emsdk:/opt/cobweb/deps/emsdk/upstream/emscripten:${PATH}"
ENV EMSDK="/opt/cobweb/deps/emsdk"
ENV EM_CONFIG="/root/.emscripten"
ENV EM_CACHE="/tmp/emcc_cache"

# build cobweb (libcob etc for wasm)
RUN cd /opt/cobweb && make all

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_cobol.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

VOLUME /src
VOLUME /out
WORKDIR /src

COPY carts/cobol/null0.cpy /usr/local/include/
COPY carts/cobol/null0_cobol_shim.c /usr/local/include/

# warm the emcc cache, so non-root users can build carts
RUN chmod -R a+rwX /root/.emscripten && \
    printf 'int main(){return 0;}' > /tmp/warm.c && \
    emcc /tmp/warm.c -s STANDALONE_WASM=1 -o /tmp/warm.wasm && \
    rm -f /tmp/warm.c /tmp/warm.wasm && \
    chmod -R a+rwX /tmp/emcc_cache

ENTRYPOINT ["build_cobol.sh"]
