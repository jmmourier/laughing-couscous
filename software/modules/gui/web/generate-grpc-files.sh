GENERATED_SOURCE_PATH=$PWD/node_modules/generated_grpc_sources
PROTO_FILES_PATH=$PWD/../src/protos

#  Generate grpc files front side

rm -rf ${GENERATED_SOURCE_PATH}
mkdir ${GENERATED_SOURCE_PATH}

./node_modules/grpc-tools/bin/protoc \
--js_out=import_style=commonjs,binary:${GENERATED_SOURCE_PATH} \
--grpc-web_out=import_style=commonjs+dts,mode=grpcwebtext:${GENERATED_SOURCE_PATH} \
-I ${PROTO_FILES_PATH} \
${PROTO_FILES_PATH}/*.proto