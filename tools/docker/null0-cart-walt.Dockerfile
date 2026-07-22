FROM node:bookworm-slim

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_walt.sh /usr/local/bin/
COPY tools/docker/walt2wasm.js /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y zip && rm -rf /var/lib/apt/lists/*

RUN npm install --prefix /opt/walt walt-compiler

VOLUME /src
VOLUME /out
WORKDIR /src

COPY carts/walt/null0.walt /usr/local/include/

ENTRYPOINT ["build_walt.sh"]
