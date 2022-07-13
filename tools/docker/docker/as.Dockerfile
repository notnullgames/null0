FROM bitnami/minideb:bullseye

WORKDIR /cart

ARG TARGETARCH

ADD https://deb.nodesource.com/node_18.x/pool/main/n/nodejs/nodejs_18.5.0-deb-1nodesource1_${TARGETARCH}.deb /tmp/nodejs.deb

RUN install_packages /tmp/nodejs.deb && \
  npm install --global assemblyscript && \
  rm /tmp/nodejs.deb
