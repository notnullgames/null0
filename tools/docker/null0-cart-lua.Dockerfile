FROM golang:1.24-bookworm

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_lua.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y zip && rm -rf /var/lib/apt/lists/*

VOLUME /src
VOLUME /out
WORKDIR /build

# build the interpreter (GopherLua + null0 bindings) once, bake it into the image.
#
# this is real go, not tinygo: lua's error-handling (pcall/error) needs
# recover(), which tinygo does not implement. it is a wasi "reactor"
# (-buildmode=c-shared) so the host can keep calling into it - a go
# command-module calls proc_exit as soon as main returns.
COPY tools/docker/lua-cart /build
RUN GOOS=wasip1 GOARCH=wasm go build -buildmode=c-shared -ldflags="-s -w" -o /usr/local/lib/main.wasm . && \
    rm -rf /root/.cache/go-build /go/pkg/mod

WORKDIR /src

ENTRYPOINT ["build_lua.sh"]
