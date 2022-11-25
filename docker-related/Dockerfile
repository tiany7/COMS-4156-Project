FROM ubuntu:20.04

ARG UNAME
ARG GNAME
ARG UID
ARG GID
ARG DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
  build-essential \
  check \
  g++ \
  zip \
  unzip \
  sudo \
  tmux \
  vim \
  git \
  tmux \
  curl \
  wget \
  libmysqlclient-dev \
  build-essential \
  # libmysqlcppconn-dev \
  autoconf \
  libtool \
  pkg-config \
  cmake \
  mysql-server \
  net-tools \
  dpkg
# bazel
RUN wget https://github.com/bazelbuild/bazel/releases/download/4.0.0/bazel-4.0.0-installer-linux-x86_64.sh
RUN chmod +x bazel-4.0.0-installer-linux-x86_64.sh
RUN ./bazel-4.0.0-installer-linux-x86_64.sh
RUN export PATH="$PATH:$HOME/bin"
RUN rm *.sh

# mysqlx/xdevapi
RUN wget https://dev.mysql.com/get/Downloads/MySQL-8.0/mysql-community-client-plugins_8.0.31-1ubuntu20.04_amd64.deb
RUN wget https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn8-2_8.0.31-1ubuntu20.04_amd64.deb
RUN wget https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn9_8.0.31-1ubuntu20.04_amd64.deb
RUN wget https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn-dev_8.0.31-1ubuntu20.04_amd64.deb
RUN dpkg -i mysql*.deb
RUN dpkg -i *8-2*.deb
RUN dpkg -i *9*.deb
RUN dpkg -i *dev*.deb
RUN rm *.deb

# redis

# kafka

# grpc is installed during bazel build

#Generates group
# RUN addgroup --gid ${GID} ${GNAME}

#Generates user
# RUN adduser --disabled-password --gecos '' --uid ${UID} --gid ${GID} --home /home/${UNAME} ${UNAME} && adduser ${UNAME} sudo && echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER root
WORKDIR /root