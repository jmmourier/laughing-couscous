FROM ubuntu:18.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    cmake \
    g++ \
    make \
    ccache \
    git \
    libssl-dev \ 
    libboost-all-dev