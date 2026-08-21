FROM debian:bookworm-slim

ARG ZIG_VERSION=0.15.2
ARG CYBER_COMMIT=master

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_cyber.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y curl xz-utils zip git perl && rm -rf /var/lib/apt/lists/*

RUN ARCH="$(uname -m)" && \
    if [ "${ARCH}" = "x86_64" ]; then ZIG_ARCH="x86_64"; else ZIG_ARCH="aarch64"; fi && \
    curl -fsSL "https://ziglang.org/download/${ZIG_VERSION}/zig-${ZIG_ARCH}-linux-${ZIG_VERSION}.tar.xz" -o /tmp/zig.tar.xz && \
    mkdir -p /opt/zig && tar -xJf /tmp/zig.tar.xz -C /opt/zig --strip-components=1 && \
    rm /tmp/zig.tar.xz && ln -s /opt/zig/zig /usr/local/bin/zig

# Cyber's public `persist_main` eval config (the only way to keep script
# state alive across separate host-triggered calls, which null0's per-frame
# callbacks need) panics on a symbol it doesn't expect to see when copying
# declarations into a later eval: @program_init/@program_deinit. This patch
# just skips those two - same fix as https://github.com/fubark/cyber upstream
# will hopefully ship eventually; not filed there per project owner's call.
RUN git clone --depth 1 --branch "${CYBER_COMMIT}" https://github.com/fubark/cyber.git /opt/cyber && \
    perl -0777 -i -pe 's/(if \(std\.mem\.eql\(u8, sym\.name\(\), "\@main_deinit"\)\) \{\n\s*continue;\n\s*\})/$1\n                            if (std.mem.eql(u8, sym.name(), "\@program_init")) {\n                                continue;\n                            }\n                            if (std.mem.eql(u8, sym.name(), "\@program_deinit")) {\n                                continue;\n                            }/s' /opt/cyber/src/compiler.zig

RUN cd /opt/cyber && zig build lib -Dtarget=wasm32-wasi -Doptimize=ReleaseSafe

COPY carts/c/null0.h /usr/local/include/
COPY tools/docker/cyber-cart.c /tmp/cyber-cart.c

# build the interpreter (Cyber VM + null0 bindings) once, bake it into the image
RUN zig cc -target wasm32-wasi -O2 \
    -I /usr/local/include -I /opt/cyber/src/include \
    /tmp/cyber-cart.c /opt/cyber/zig-out/lib/libcyber.a \
    -o /usr/local/lib/main.wasm && \
    rm /tmp/cyber-cart.c

VOLUME /src
VOLUME /out
WORKDIR /src

ENTRYPOINT ["build_cyber.sh"]
