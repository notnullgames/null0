FROM konsumer/null0:c

WORKDIR /cart

ENV PATH="/opt/nelua:${PATH}"

ADD https://codeload.github.com/edubart/nelua-lang/tar.gz/refs/tags/latest /opt/nelua.tgz
RUN cd /opt && \
    tar -xvzf nelua.tgz && \
    cd /opt/nelua-lang-latest && \
    make && \
    mkdir /opt/nelua && \
    mv /opt/nelua-lang-latest/nelua /opt/nelua-lang-latest/nelua-lua /opt/nelua-lang-latest/lib /opt/nelua-lang-latest/lualib /opt/nelua/ && \
    rm -rf /opt/nelua-lang-latest /opt/nelua.tgz
