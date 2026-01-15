FROM konsumer/null0-cart-c:latest

COPY tools/docker/build_quickjs.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

ADD https://github.com/quickjs-ng/quickjs/archive/refs/heads/master.zip /tmp/quickjs-ng.zip
RUN cd /tmp/ && unzip quickjs-ng.zip
COPY tools/docker/quickjs-cart.c /tmp/quickjs-master/qjs.c

# build cart wasm & wipe source
RUN cd /tmp/quickjs-master && \
  ls /usr/local/include && \
  /opt/wasi-sdk/bin/clang -O3 -Wl,--initial-memory=1310720 -Wl,--max-memory=13107200 -D_WASI_EMULATED_SIGNAL -DCONFIG_VERSION=wasi -DCONFIG_BIGNUM=y -DCONFIG_WASI=y -I /usr/local/include -o /usr/local/lib/main.wasm qjs.c libunicode.c cutils.c libregexp.c quickjs.c quickjs-libc.c && \
  rm -rf /tmp/quickjs-master /tmp/quickjs-ng.zip

ENTRYPOINT ["build_quickjs.sh"]