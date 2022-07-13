ARG WASI_VERSION=16

FROM bitnami/minideb:bullseye AS downloader

ARG WASI_VERSION
ENV WASI_VERSION=$WASI_VERSION
ENV WASI_VERSION_FULL=${WASI_VERSION}.0

ADD https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-${WASI_VERSION}/wasi-sdk-${WASI_VERSION_FULL}-linux.tar.gz /opt/wasi-sdk.tar.gz


FROM bitnami/minideb:bullseye AS final

WORKDIR /cart
ARG WASI_VERSION
ENV WASI_VERSION=$WASI_VERSION
ENV WASI_VERSION_FULL=${WASI_VERSION}.0
ENV WASI_SDK_PATH=/opt/wasi-sdk

COPY --from=downloader  /opt/wasi-sdk.tar.gz /opt/wasi-sdk.tar.gz
RUN cd /opt && tar xvzf wasi-sdk.tar.gz && rm wasi-sdk.tar.gz && mv wasi-sdk-${WASI_VERSION_FULL} ${WASI_SDK_PATH} && install_packages build-essential libxml2-dev binaryen