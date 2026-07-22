FROM rust:1-bookworm

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_rust.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y zip && rm -rf /var/lib/apt/lists/*
RUN rustup target add wasm32-unknown-unknown

VOLUME /src
VOLUME /out
WORKDIR /src

COPY carts/rust/Cargo.toml /usr/local/include/null0rust/Cargo.toml
COPY carts/rust/src /usr/local/include/null0rust/src

ENTRYPOINT ["build_rust.sh"]
