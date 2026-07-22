FROM debian:bookworm-slim

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_d.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y ldc lld zip && rm -rf /var/lib/apt/lists/*

VOLUME /src
VOLUME /out
WORKDIR /src

COPY carts/d/null0.d /usr/local/include/

ENTRYPOINT ["build_d.sh"]
