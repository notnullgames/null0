FROM debian:bookworm-slim

ARG ZIG_VERSION=0.14.1

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_zig.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y curl xz-utils zip && rm -rf /var/lib/apt/lists/*

RUN ARCH="$(uname -m)" && \
    if [ "${ARCH}" = "x86_64" ]; then ZIG_ARCH="x86_64"; else ZIG_ARCH="aarch64"; fi && \
    curl -fsSL "https://ziglang.org/download/${ZIG_VERSION}/zig-${ZIG_ARCH}-linux-${ZIG_VERSION}.tar.xz" -o /tmp/zig.tar.xz && \
    mkdir -p /opt/zig && tar -xJf /tmp/zig.tar.xz -C /opt/zig --strip-components=1 && \
    rm /tmp/zig.tar.xz && ln -s /opt/zig/zig /usr/local/bin/zig

VOLUME /src
VOLUME /out
WORKDIR /src

COPY carts/zig/null0.zig /usr/local/include/

ENTRYPOINT ["build_zig.sh"]
