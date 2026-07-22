FROM debian:bookworm-slim

ARG ONYX_VERSION=0.1.13-beta

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_onyx.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y curl zip && rm -rf /var/lib/apt/lists/*

RUN ARCH="$(uname -m)" && \
    if [ "${ARCH}" = "x86_64" ]; then ONYX_ARCH="amd64"; else ONYX_ARCH="arm64"; fi && \
    curl -fsSL "https://github.com/onyx-lang/onyx/releases/download/v${ONYX_VERSION}/onyx-linux-ovm-${ONYX_ARCH}.tar.gz" -o /tmp/onyx.tar.gz && \
    mkdir -p /opt/onyx && tar -xzf /tmp/onyx.tar.gz -C /opt/onyx && \
    rm /tmp/onyx.tar.gz

ENV PATH="/opt/onyx/bin:${PATH}"
ENV ONYX_PATH="/opt/onyx"

VOLUME /src
VOLUME /out
WORKDIR /src

COPY carts/onyx/null0.onyx /usr/local/include/

ENTRYPOINT ["build_onyx.sh"]
