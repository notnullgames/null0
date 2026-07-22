FROM debian:bookworm-slim

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_python.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y curl zip && rm -rf /var/lib/apt/lists/*

# py2wasm runs as a wasmer package
RUN curl https://get.wasmer.io -sSfL | sh

ENV PATH="/root/.wasmer/bin:${PATH}"

VOLUME /src
VOLUME /out
WORKDIR /src

COPY carts/python/null0 /usr/local/include/null0py

ENTRYPOINT ["build_python.sh"]
