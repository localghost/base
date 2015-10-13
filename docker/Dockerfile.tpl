FROM ubuntu:15.10

ENV DEBIAN_FRONTEND noninteractive

RUN sed -i 's|http://archive|http://pl.archive|g' /etc/apt/sources.list

RUN apt-get update
RUN apt-get install -y g++
RUN apt-get install -y cmake
RUN apt-get install -y libboost-dev
RUN apt-get install -y libboost-system-dev
RUN apt-get install -y libboost-filesystem-dev
RUN apt-get install -y libboost-test-dev
RUN apt-get install -y vim

RUN addgroup {username} --gid {gid}
RUN adduser {username} --uid {uid} --gid {gid}

USER {username}

CMD /bin/bash
