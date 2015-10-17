FROM ubuntu:15.10

ENV DEBIAN_FRONTEND noninteractive

#RUN sed -i 's|http://archive|http://pl.archive|g' /etc/apt/sources.list

RUN apt-get update
RUN apt-get install -y g++
RUN apt-get install -y cmake
RUN apt-get install -y libboost-dev
RUN apt-get install -y libboost-system-dev
RUN apt-get install -y libboost-filesystem-dev
RUN apt-get install -y libboost-test-dev
RUN apt-get install -y vim
RUN apt-get install -y wget
RUN apt-get install -y default-jre
RUN apt-get install -y ubuntu-artwork
RUN apt-get install -y sudo
RUN apt-get install -y fonts-droid

# setup Eclipse
RUN wget http://artfiles.org/eclipse.org//technology/epp/downloads/release/mars/1/eclipse-cpp-mars-1-linux-gtk-x86_64.tar.gz -O /tmp/eclipse.tgz --no-verbose
RUN tar -C /opt -xzf /tmp/eclipse.tgz
RUN rm -f /tmp/eclipse.tgz
RUN ln -s /opt/eclipse/eclipse /usr/local/bin

RUN groupadd --gid {gid} {username}
RUN useradd --uid {uid} --gid {gid} -G sudo -m {username}

USER {username}
WORKDIR /home/{username}

CMD /bin/bash
