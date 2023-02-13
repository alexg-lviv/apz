FROM apz_image:latest
COPY . /usr/src/logging-service
WORKDIR /usr/src/logging-service
RUN cmake . -DIN_DOCKER=1 && \
    make && /sbin/ldconfig -v

CMD ["./Logging_service"]
