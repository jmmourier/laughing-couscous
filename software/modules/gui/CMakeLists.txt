cmake_minimum_required (VERSION 3.0)

# web server
set(_REFLECTION grpc++_reflection)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
set(GENERATED_GRPC_BACKEND_SOURCE_PATH "${CMAKE_CURRENT_BINARY_DIR}/generated")

file(MAKE_DIRECTORY ${GENERATED_GRPC_BACKEND_SOURCE_PATH})

get_filename_component(robot_proto "src/protos/robot.proto" ABSOLUTE)
get_filename_component(robot_proto_path "${robot_proto}" PATH)

function(protobuf_generate_grpc_cpp)
  if(NOT ARGN)
    message(SEND_ERROR "Error: PROTOBUF_GENERATE_GRPC_CPP() called without any proto files")
    return()
  endif()

  foreach(FIL ${ARGN})
      get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
      get_filename_component(FIL_WE ${FIL} NAME_WE)
      add_custom_command(
        OUTPUT "${GENERATED_GRPC_BACKEND_SOURCE_PATH}/${FIL_WE}.grpc.pb.cc"
              "${GENERATED_GRPC_BACKEND_SOURCE_PATH}/${FIL_WE}.grpc.pb.h"
              "${GENERATED_GRPC_BACKEND_SOURCE_PATH}/${FIL_WE}.pb.cc"
              "${GENERATED_GRPC_BACKEND_SOURCE_PATH}/${FIL_WE}.pb.h"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${GENERATED_GRPC_BACKEND_SOURCE_PATH}"
             --cpp_out "${GENERATED_GRPC_BACKEND_SOURCE_PATH}"
             -I "${robot_proto_path}"
             --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
             ${robot_proto}
        DEPENDS ${ABS_FIL}
        COMMENT "Running gRPC C++ protocol buffer compiler on ${FIL}")
  endforeach()
endfunction()

protobuf_generate_grpc_cpp(src/protos/robot.proto)

file(GLOB_RECURSE WEB_SERVER_HEADERS include/**.h src/**.h)

list(APPEND SOURCES
        src/WebServer.cpp
        src/WebPositionService.cpp
)

# Library
add_library(
        webserver
        STATIC ${SOURCES}
        ${GENERATED_GRPC_BACKEND_SOURCE_PATH}/robot.grpc.pb.cc
        ${GENERATED_GRPC_BACKEND_SOURCE_PATH}/robot.pb.cc
        ${WEB_SERVER_HEADERS}
)

target_include_directories(
        webserver
        PUBLIC  include
        src
        ${PROTOBUF_INCLUDE_DIR}
        ${GENERATED_GRPC_BACKEND_SOURCE_PATH}
)

target_link_libraries(webserver
        PUBLIC ${_GRPC_GRPCPP}
        ${_REFLECTION}
        ${_PROTOBUF_LIBPROTOBUF}
)