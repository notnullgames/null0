# The C image is the base (wasi-sdk + zipcart + null0.h). CI overrides BASE
# with the one it just built, so this image is never assembled on top of a
# previously-published C image that predates the bindings it's baking in.
ARG BASE=ghcr.io/notnullgames/null0-cart-c:latest
FROM ${BASE}

COPY tools/docker/build_nelua.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y build-essential git gcc && \
  git clone https://github.com/edubart/nelua-lang.git /tmp/nelua && \
  cd /tmp/nelua && \
  make && make install

RUN apt-get purge -y build-essential git gcc && apt-get autoremove -y && rm -rf /var/lib/apt/lists/* /tmp/nelua

COPY carts/nelua/null0.nelua /usr/local/include

ENTRYPOINT ["build_nelua.sh"]