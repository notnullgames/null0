FROM konsumer/null0-cart-c:latest

COPY tools/docker/build_nim.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y nim && rm -rf /var/lib/apt/lists/*

COPY carts/nim/null0.nim /usr/local/include

ENTRYPOINT ["build_nim.sh"]