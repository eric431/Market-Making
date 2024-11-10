FROM --platform=linux/amd64 ubuntu:latest

USER root

RUN apt-get update || (sleep 30 && apt-get update) && \
    apt-get install -y libc6-i386 rlwrap unzip tree \
    && apt-get clean \
    && usermod -aG sudo root

WORKDIR /root
COPY /kdb/q /root/q
COPY /kdb/qscripts /root/qscripts
COPY /scripts/docker_entrypoint.sh /root/entrypoint.sh

RUN chown -R root /root/qscripts \
    && chown -R root /root/q \
    && chmod 755 /root/q/l64/q \
    && chmod +x /root/entrypoint.sh \
    && chmod +x /root/q/kc.lic

ENV QHOME=/root/q
ENV QBIN=${QHOME}/l64/q
ENV PATH=${PATH}:${QHOME}
    
EXPOSE 1234
ENTRYPOINT [ "/root/entrypoint.sh" ]

# CMD ["\$QBIN", "-c", "/q/kc.lic", "\$QHOME/script.q"]
