FROM ubuntu:18.04

RUN echo 'APT{Install-Recommends "0";Install-Suggests "0";};' > /etc/apt/apt.conf.d/zzzuser
RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get upgrade -qyy && apt-get autoremove -qyy --purge
RUN DEBIAN_FRONTEND=noninteractive apt-get install -qyy socat

RUN adduser --no-create-home --disabled-login --gecos '' -- "linux_forest" && mkdir -p "/home/linux_forest"

COPY --chown=root:linux_forest ./private/flag /home/linux_forest/flag
COPY --chown=root:linux_forest ./public/main /home/linux_forest/


RUN chmod 0440 "/home/linux_forest/flag" && \
    chmod 0755 "/home/linux_forest/main"

WORKDIR /home/linux_forest
EXPOSE 7182/tcp
CMD ["socat", "TCP-LISTEN:7182,reuseaddr,fork", "EXEC:/home/linux_forest/main,nofork,stderr,setsid,su=linux_forest"]
