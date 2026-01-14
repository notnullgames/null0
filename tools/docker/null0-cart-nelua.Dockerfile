FROM konsumer/null0-cart-c:latest

COPY tools/docker/build_nelua.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y build-essential git gcc && \
  git clone https://github.com/edubart/nelua-lang.git /tmp/nelua && \
  cd /tmp/nelua && \
  make && make install

RUN apt-get purge -y build-essential git gcc && apt-get autoremove -y && rm -rf /var/lib/apt/lists/* /tmp/nelua

COPY carts/nelua/null0.nelua /usr/local/include

ENTRYPOINT ["build_nelua.sh"]