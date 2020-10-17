# build grcp cpp plugin to generate grpc files when cross compiling

mkdir -p software/external/grpc/cmake/build

pushd "software/external/grpc/cmake/build"

cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DgRPC_SSL_PROVIDER=package \
    -DgRPC_INSTALL=ON \
    -DgRPC_BUILD_CSHARP_EXT=OFF \
    -DgRPC_BUILD_GRPC_CSHARP_PLUGIN=OFF \
    -DgRPC_BUILD_GRPC_OBJECTIVE_C_PLUGIN=OFF \
    -DgRPC_BUILD_GRPC_PHP_PLUGIN=OFF \
    -DgRPC_BUILD_GRPC_PYTHON_PLUGIN=OFF \
    -DgRPC_BUILD_GRPC_RUBY_PLUGIN=OFF \
    -DgRPC_BUILD_GRPC_NODE_PLUGIN=OFF \
    -DgRPC_BUILD_TESTS=OFF \
../..

make -j8 install