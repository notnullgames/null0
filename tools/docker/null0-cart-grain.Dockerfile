FROM --platform=linux/amd64 debian:bookworm-slim

ARG GRAIN_VERSION=0.7.2

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_grain.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y curl zip && rm -rf /var/lib/apt/lists/*

# grain only publishes linux-x64 binaries
RUN curl -fsSL "https://github.com/grain-lang/grain/releases/download/grain-v${GRAIN_VERSION}/grain-linux-x64" -o /usr/local/bin/grain && \
    chmod +x /usr/local/bin/grain

VOLUME /src
VOLUME /out
WORKDIR /src

COPY carts/grain/null0.gr /usr/local/include/

ENTRYPOINT ["build_grain.sh"]
