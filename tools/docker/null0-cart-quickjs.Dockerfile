FROM konsumer/null0-cart-c:latest

COPY tools/docker/build_quickjs.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

COPY tools/docker/quickjs-cart /usr/local/include/quickjs/

# build cart wasm & wipe source
RUN cd /usr/local/include/quickjs/ && \
  clang -O3 -Wl,--initial-memory=1310720 -Wl,--max-memory=13107200 -D_WASI_EMULATED_SIGNAL -DCONFIG_VERSION=wasi -DCONFIG_BIGNUM=y -o /usr/local/lib/main.wasm -I /usr/local/include main.c libunicode.c cutils.c libbf.c libregexp.c quickjs.c quickjs-libc.c qjscalc.c && \
  rm -rf /usr/local/include/quickjs

ENTRYPOINT ["build_quickjs.sh"]