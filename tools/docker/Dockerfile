FROM ubuntu:18.04

ARG CLANG_VERSION=10
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get -y install --no-install-recommends \
    ca-certificates \
    clang-${CLANG_VERSION} \
    clang-tidy-${CLANG_VERSION} \
    clang-format-${CLANG_VERSION} \
    vim \
    wget \
    unzip \
    ssh \
    cmake \
    g++ \
    make \
    ccache \
    git \
    libssl-dev \ 
    libboost-all-dev

RUN wget -O /usr/bin/protoc-gen-grpc-web \
    https://github.com/grpc/grpc-web/releases/download/1.0.7/protoc-gen-grpc-web-1.0.7-linux-x86_64 --no-check-certificate

RUN chmod +x /usr/bin/protoc-gen-grpc-web

WORKDIR /usr

RUN wget https://github.com/clangd/clangd/releases/download/11.0.0-rc1/clangd-linux-11.0.0-rc1.zip --no-check-certificate
RUN unzip clangd-linux-11.0.0-rc1.zip \
    && cp -r clangd_11.0.0-rc1/* . \
    && rm -rf clangd_11.0.0-rc1 && \
    rm -rf clangd-linux-11.0.0-rc1.zip

# create workspace folder
RUN mkdir -p /workspace/laughing-couscous-dev