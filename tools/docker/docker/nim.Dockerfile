FROM konsumer/null0:c

WORKDIR /cart

ADD https://nim-lang.org/download/nim-1.6.6.tar.xz /tmp/nim-1.6.6.tar.xz

RUN cd /tmp && \
  tar -xf nim-1.6.6.tar.xz && \
  cd nim-1.6.6 && \
  sh build.sh && \
  bin/nim c koch && \
  ./koch boot -d:release && \
  ./koch tools && \
  rm -rf /tmp/nim*
