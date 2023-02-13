FROM apz_image:latest
COPY . /usr/src/facade-service
WORKDIR /usr/src/facade-service
RUN apt-get install uuid-dev && \
    cmake . -DIN_DOCKER=1 && \
    make && /sbin/ldconfig -v

CMD ["./Messages_service"]
