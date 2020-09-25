FROM ubuntu:18.04
ARG CLANG_VERSION=10

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
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
WORKDIR /usr

RUN wget https://github.com/clangd/clangd/releases/download/11.0.0-rc1/clangd-linux-11.0.0-rc1.zip --no-check-certificate
RUN unzip clangd-linux-11.0.0-rc1.zip \
    && cp -r clangd_11.0.0-rc1/* . \
    && rm -rf clangd_11.0.0-rc1 && \
    rm -rf clangd-linux-11.0.0-rc1.zip