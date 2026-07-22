FROM debian:bookworm-slim

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_wat.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y wabt zip && rm -rf /var/lib/apt/lists/*

VOLUME /src
VOLUME /out
WORKDIR /src

COPY carts/wat/null0.wat /usr/local/include/

ENTRYPOINT ["build_wat.sh"]
