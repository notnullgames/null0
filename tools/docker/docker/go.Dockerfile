FROM bitnami/minideb:bullseye

WORKDIR /setup

ARG TARGETARCH
ENV PATH="/opt/tinygo/bin:${PATH}"

ADD https://github.com/tinygo-org/tinygo/releases/download/v0.24.0/tinygo0.24.0.linux-${TARGETARCH}.tar.gz /opt/tinygo.tar.gz
RUN cd /opt && \
    tar -xf tinygo.tar.gz && \
    rm tinygo.tar.gz && \
    install_packages golang

