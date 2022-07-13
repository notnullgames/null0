FROM konsumer/null0:c

WORKDIR /cart
ARG TARGETARCH

RUN install_packages cargo
