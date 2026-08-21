FROM ghcr.io/webassembly/wasi-sdk:latest

ARG JIK_VERSION=0.1.0-alpha.22

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_jik.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y curl zip && rm -rf /var/lib/apt/lists/*

# Download Jik compiler (linux-x64)
RUN curl -fsSL "https://github.com/jik-lang/jik/releases/download/v${JIK_VERSION}/jik-v${JIK_VERSION}-linux-x64.tar.gz" -o /tmp/jik.tar.gz && \
    mkdir -p /opt/jik && tar -xzf /tmp/jik.tar.gz -C /opt/jik && \
    rm /tmp/jik.tar.gz && \
    find /opt/jik -name jik -type f -executable -exec ln -s {} /usr/local/bin/jik \; && \
    jik help

VOLUME /src
VOLUME /out
WORKDIR /src

ENV PATH="/opt/wasi-sdk/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
ENV WASI_SDK_DIR="/opt/wasi-sdk"

COPY carts/c/null0.h /usr/local/include/
COPY carts/jik/null0.jik /usr/local/include/

ENTRYPOINT ["build_jik.sh"]
