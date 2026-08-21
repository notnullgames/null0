FROM ghcr.io/webassembly/wasi-sdk:latest

ARG HAXE_VERSION=4.3.6
ARG HL_VERSION=1.14

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_haxe.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y curl zip ca-certificates && rm -rf /var/lib/apt/lists/*

# haxe compiler (no haxelib: carts have no dependencies, and HL/C generation
# shells out to haxelib for the native build step - a no-op shim skips it)
RUN curl -fsSL "https://github.com/HaxeFoundation/haxe/releases/download/${HAXE_VERSION}/haxe-${HAXE_VERSION}-linux64.tar.gz" -o /tmp/haxe.tar.gz && \
    mkdir -p /opt/haxe && tar -xzf /tmp/haxe.tar.gz -C /opt/haxe --strip-components=1 && \
    rm /tmp/haxe.tar.gz && \
    ln -s /opt/haxe/haxe /usr/local/bin/haxe && \
    printf '#!/bin/sh\nexit 0\n' > /usr/local/bin/haxelib && \
    chmod +x /usr/local/bin/haxelib && \
    haxe --version

ENV HAXE_STD_PATH=/opt/haxe/std

# hashlink runtime sources (haxe HL/C output is compiled against these)
RUN curl -fsSL "https://github.com/HaxeFoundation/hashlink/archive/refs/tags/${HL_VERSION}.tar.gz" -o /tmp/hl.tar.gz && \
    tar -xzf /tmp/hl.tar.gz -C /opt && \
    mv /opt/hashlink-${HL_VERSION} /opt/hashlink && \
    rm /tmp/hl.tar.gz

VOLUME /src
VOLUME /out
WORKDIR /src

ENV PATH="/opt/wasi-sdk/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/bin"

# runtime glue (hlc_main.c shadow, wasi stubs) + generated C shim
COPY tools/docker/haxe-cart/ /opt/null0-haxe/

# generated haxe bindings
COPY carts/haxe/Null0.hx /opt/null0-haxe/Null0.hx

ENTRYPOINT ["build_haxe.sh"]
