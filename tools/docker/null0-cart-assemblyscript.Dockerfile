FROM node:latest

COPY tools/docker/zipcart.sh /usr/local/bin/
COPY tools/docker/build_assemblyscript.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/*

RUN apt-get update && apt-get install -y zip && rm -rf /var/lib/apt/lists/*

VOLUME /src
VOLUME /out
WORKDIR /src

RUN npm i -g assemblyscript

COPY carts/as/null0.ts /usr/local/include/

ENTRYPOINT ["build_assemblyscript.sh"]