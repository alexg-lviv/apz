FROM gcc:latest
#COPY . /usr/src/test
WORKDIR /usr/src/test
RUN apt-get update && \
    apt-get -y install cmake && \
    apt-get -y install make && \
    apt-get install -y libmicrohttpd-dev && \
    apt-get -y install libspdlog-dev && \
    git clone https://github.com/libcpr/cpr.git && \
    cd cpr && mkdir build && cd build && \
    cmake .. -DCPR_USE_SYSTEM_CURL=ON && \
    cmake --build . && \
    cmake --install . && \
    cd .. && cd .. && \
    git clone https://github.com/etr/libhttpserver && \
    cd libhttpserver && \
    ./bootstrap && \
    mkdir build && \
    cd build && \
    ../configure && \
    make && \
    make install
#RUN chmod u+x ./compile.sh && ./compile.sh
#CMD ["./build/Facade_service"]