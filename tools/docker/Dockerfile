FROM ubuntu:20.04

ARG CLANG_VERSION=10
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get -y install --no-install-recommends \
    ca-certificates \   
    gdb \
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
    libboost-all-dev \
    sshpass \
    rsync \
    ansible

### Install NodeJS
RUN wget -qO- https://deb.nodesource.com/setup_15.x | bash
RUN apt-get -y install nodejs
RUN npm install -g yarn

RUN wget -O /usr/bin/protoc-gen-grpc-web \
    https://github.com/grpc/grpc-web/releases/download/1.0.7/protoc-gen-grpc-web-1.0.7-linux-x86_64 --no-check-certificate
RUN chmod +x /usr/bin/protoc-gen-grpc-web

WORKDIR /usr
RUN wget https://github.com/clangd/clangd/releases/download/11.0.0/clangd-linux-11.0.0.zip --no-check-certificate
RUN unzip clangd-linux-11.0.0.zip \
    && cp -r clangd_11.0.0/* . \
    && rm -rf clangd_11.0.0 && \
    rm -rf clangd-linux-11.0.0.zip

# create workspace folder
RUN mkdir -p /workspace/laughing-couscous

WORKDIR /tmp

# clone grpc repo and install its submodules
RUN git clone https://github.com/grpc/grpc.git && \
    cd grpc && \
    git submodule update --init --recursive && \
    mkdir -p "cmake/build" 

WORKDIR /tmp/grpc/cmake/build

# compile and install grpc 
RUN cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DgRPC_INSTALL=ON \
    -DgRPC_BUILD_TESTS=OFF \
    -DgRPC_SSL_PROVIDER=package \
    ../.. && \
    make -j$(nproc) install

WORKDIR /tmp

RUN mkdir -p mkdir -p raspberrypi_root && \
    cd raspberrypi_root && \
    git clone https://github.com/raspberrypi/tools raspberrypi-tools && \
    cd raspberrypi-tools && git checkout 4a335520900ce55e251ac4f420f52bf0b2ab6b1f

RUN echo " \n\
    SET(CMAKE_SYSTEM_NAME Linux) \n\
    SET(CMAKE_SYSTEM_PROCESSOR arm) \n\
    set(devel_root /tmp/raspberrypi_root) \n\
    set(CMAKE_STAGING_PREFIX \${devel_root}/stage) \n\
    set(tool_root \${devel_root}/raspberrypi-tools/arm-bcm2708) \n\
    set(CMAKE_SYSROOT \${tool_root}/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot) \n\
    set(CMAKE_C_COMPILER \${tool_root}/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc) \n\
    set(CMAKE_CXX_COMPILER \${tool_root}/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++) \n\
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER) \n\
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY) \n\
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY) \n\
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY) \n\
    " >> /tmp/toolchain.cmake

WORKDIR /tmp/grpc/cmake

RUN mkdir -p raspberrypi_build

WORKDIR /tmp/grpc/cmake/raspberrypi_build

RUN cmake -DCMAKE_TOOLCHAIN_FILE=/tmp/toolchain.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/tmp/raspberrypi_root/grpc_install \
    ../.. && \
    make -j$(nproc) install