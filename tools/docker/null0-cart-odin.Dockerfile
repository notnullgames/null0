FROM debian:bookworm-slim

ARG ODIN_VERSION=dev-2026-07a

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_odin.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y curl xz-utils zip clang lld llvm && rm -rf /var/lib/apt/lists/*

RUN ARCH="$(uname -m)" && \
    if [ "${ARCH}" = "x86_64" ]; then ODIN_ARCH="amd64"; else ODIN_ARCH="arm64"; fi && \
    curl -fsSL "https://github.com/odin-lang/Odin/releases/download/${ODIN_VERSION}/odin-linux-${ODIN_ARCH}-${ODIN_VERSION}.tar.gz" -o /tmp/odin.tar.gz && \
    mkdir -p /opt/odin && tar -xzf /tmp/odin.tar.gz -C /opt/odin --strip-components=1 && \
    rm /tmp/odin.tar.gz && \
    ln -s /opt/odin/odin /usr/local/bin/odin && \
    odin version

VOLUME /src
VOLUME /out
WORKDIR /src

COPY carts/odin/null0 /usr/local/include/null0odin

ENTRYPOINT ["build_odin.sh"]
