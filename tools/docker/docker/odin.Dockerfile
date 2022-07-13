FROM konsumer/null0:c

WORKDIR /cart

ARG TARGETARCH

ENV PATH="/opt/odin:${PATH}"

RUN install_packages git clang llvm-dev && \
    cd /opt && \
    git clone -c http.sslVerify=false https://github.com/odin-lang/Odin.git odin && \
    cd odin && \
    ./build_odin.sh release && \
    rm -rf /opt/odin/.git
