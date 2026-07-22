FROM debian:bookworm-slim

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_never.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y git cmake build-essential bison flex libffi-dev zip && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 https://github.com/never-lang/never.git /tmp/never && \
    mkdir -p /tmp/never/build && cd /tmp/never/build && cmake .. && make && \
    cp never /usr/local/bin/ && rm -rf /tmp/never

VOLUME /src
VOLUME /out
WORKDIR /src

COPY carts/never/null0.nev /usr/local/include/

ENTRYPOINT ["build_never.sh"]
