FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    openssh \
    rlwrap \
    unzip \
    runit \
    curl \
    && apt-get clean

ENV QHOME /kdb
ENV PATH ${PATH}:${HOME}

COPY ./kdb/ /kdb
WORKDIR kdb
CMD ["q", "example.q","-p","1234"]


