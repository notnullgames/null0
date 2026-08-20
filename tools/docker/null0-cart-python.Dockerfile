FROM rust:1-bookworm

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_python.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y zip && rm -rf /var/lib/apt/lists/*
RUN rustup target add wasm32-wasip1

VOLUME /src
VOLUME /out
WORKDIR /build

# build the interpreter (RustPython + null0 bindings) once, bake it into the image
COPY tools/docker/python-cart /build
RUN cargo build --target wasm32-wasip1 --release && \
    cp target/wasm32-wasip1/release/main.wasm /usr/local/lib/main.wasm && \
    rm -rf /build/target /root/.cargo/registry /root/.cargo/git

WORKDIR /src

ENTRYPOINT ["build_python.sh"]
