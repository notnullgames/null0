FROM --platform=linux/amd64 debian:bookworm-slim

ARG C3_VERSION=0.8.2

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_c3.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y curl zip && rm -rf /var/lib/apt/lists/*

# c3 publishes a fully-static linux build (x86_64 only)
RUN curl -fsSL "https://github.com/c3lang/c3c/releases/download/v${C3_VERSION}/c3-linux-static.tar.gz" -o /tmp/c3.tar.gz && \
    mkdir -p /opt/c3 && tar -xzf /tmp/c3.tar.gz -C /opt/c3 && \
    rm /tmp/c3.tar.gz && \
    C3_BIN="$(find /opt/c3 -name c3c -type f | head -1)" && \
    ln -s "${C3_BIN}" /usr/local/bin/c3c && \
    c3c --version

VOLUME /src
VOLUME /out
WORKDIR /src

COPY carts/c3/null0.c3 /usr/local/include/

ENTRYPOINT ["build_c3.sh"]
