FROM ubuntu:latest

USER root

RUN apt-get update && apt-get install -y \
    rlwrap \
    unzip \
    runit \
    curl  


ENV QHOME /kdb
ENV QLIC /kdb/kc.lic
ENV PATH ${PATH}:${QHOME}

RUN alias q='QHOME=~/q rlwrap -r ~/q/l64/q' \
    && echo "DONE!"

WORKDIR ${QHOME}
COPY ./../../kdb/ ${QHOME}

EXPOSE 1234

CMD ["q", "example.q","-p","1234"]


