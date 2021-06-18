FROM ubuntu:20.04 as builder

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get -y install --no-install-recommends \
    ca-certificates \   
    wget \
    unzip \
    ssh \
    cmake \
    g++ \
    make \
    git \
    libssl-dev \ 
    sshpass

WORKDIR /build

RUN wget -O protoc-gen-grpc-web \
    https://github.com/grpc/grpc-web/releases/download/1.0.7/protoc-gen-grpc-web-1.0.7-linux-x86_64 --no-check-certificate
RUN chmod +x protoc-gen-grpc-web

RUN wget https://github.com/clangd/clangd/releases/download/11.0.0/clangd-linux-11.0.0.zip --no-check-certificate
RUN unzip clangd-linux-11.0.0.zip

# create workspace folder
RUN mkdir -p /workspace/laughing-couscous

WORKDIR /build

# clone grpc repo and install its submodules
RUN git clone https://github.com/grpc/grpc.git && \
    cd grpc && \
    git checkout 257d0045ab958eb767a3591c88e9d0c2bdf4b916 && \
    git submodule update --init --recursive && \
    mkdir -p "cmake/build" 

WORKDIR /build/grpc/cmake/build

# compile and install grpc 
RUN cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DgRPC_INSTALL=ON \
    -DgRPC_BUILD_TESTS=OFF \
    -DgRPC_SSL_PROVIDER=package \
    ../.. && \
    make -j$(nproc) install

WORKDIR /build

RUN mkdir -p raspberrypi_root && \
    cd raspberrypi_root && \
    git clone https://github.com/raspberrypi/tools raspberrypi-tools && \
    cd raspberrypi-tools && git checkout 4a335520900ce55e251ac4f420f52bf0b2ab6b1f

RUN echo " \n\
    SET(CMAKE_SYSTEM_NAME Linux) \n\
    SET(CMAKE_SYSTEM_PROCESSOR arm) \n\
    set(devel_root /build/raspberrypi_root) \n\
    set(CMAKE_STAGING_PREFIX \${devel_root}/stage) \n\
    set(tool_root \${devel_root}/raspberrypi-tools/arm-bcm2708) \n\
    set(CMAKE_SYSROOT \${tool_root}/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot) \n\
    set(CMAKE_C_COMPILER \${tool_root}/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc) \n\
    set(CMAKE_CXX_COMPILER \${tool_root}/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++) \n\
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER) \n\
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY) \n\
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY) \n\
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY) \n\
    " >> /build/toolchain.cmake

WORKDIR /build/grpc/cmake

RUN mkdir -p raspberrypi_build

WORKDIR /build/grpc/cmake/raspberrypi_build

RUN cmake -DCMAKE_TOOLCHAIN_FILE=/build/toolchain.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/build/raspberrypi_root/grpc_install \
    ../.. && \
    make -j$(nproc) install

FROM ubuntu:20.04 as image_dev_dependencies

ARG DEBIAN_FRONTEND=noninteractive
RUN apt clean && \ 
    apt-get update && \
    apt-get -y install --no-install-recommends \
    ca-certificates \   
    gdb \
    wget \
    ssh \
    cmake \
    g++ \
    make \
    ccache \
    git \
    libssl-dev \ 
    sshpass \
    rsync \
    ansible

### Install NodeJS
RUN wget -qO- https://deb.nodesource.com/setup_15.x | bash && \
    apt-get -y install nodejs && \
    npm install -g yarn

FROM image_dev_dependencies as image_dev 

COPY --from=builder /build/clangd_11.0.0 /usr
COPY --from=builder /usr /usr
COPY --from=builder /build/protoc-gen-grpc-web /usr/bin/protoc-gen-grpc-web
COPY --from=builder /build/raspberrypi_root/grpc_install /build/raspberrypi_root/grpc_install
COPY --from=builder /build/raspberrypi_root/stage /build/raspberrypi_root/stage
COPY --from=builder /build/raspberrypi_root/raspberrypi-tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf /build/raspberrypi_root/raspberrypi-tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf
COPY --from=builder /build/raspberrypi_root/raspberrypi-tools/arm-bcm2708/arm-linux-gnueabihf /build/raspberrypi_root/raspberrypi-tools/arm-bcm2708/arm-linux-gnueabihf
COPY --from=builder /build/toolchain.cmake /build/toolchain.cmake