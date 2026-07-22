FROM golang:1.24-bookworm

ARG TINYGO_VERSION=0.39.0

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_go.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y curl zip && rm -rf /var/lib/apt/lists/*

RUN ARCH="$(dpkg --print-architecture)" && \
    curl -fsSL "https://github.com/tinygo-org/tinygo/releases/download/v${TINYGO_VERSION}/tinygo${TINYGO_VERSION}.linux-${ARCH}.tar.gz" -o /tmp/tinygo.tar.gz && \
    tar -xzf /tmp/tinygo.tar.gz -C /usr/local && \
    rm /tmp/tinygo.tar.gz

ENV PATH="/usr/local/tinygo/bin:${PATH}"

VOLUME /src
VOLUME /out
WORKDIR /src

COPY carts/go/null0 /usr/local/include/null0go

ENTRYPOINT ["build_go.sh"]
