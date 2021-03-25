cmake_minimum_required (VERSION 3.0)
project(webserver
        VERSION 1.0
        LANGUAGES CXX
        )

# web server
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
  find_program(_PROTOBUF_PROTOC protoc)
else()
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

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

find_package(Threads REQUIRED)

# Library
add_library(
        ${PROJECT_NAME}_lib
        STATIC ${SOURCES}
        ${GENERATED_GRPC_BACKEND_SOURCE_PATH}/robot.grpc.pb.cc
        ${GENERATED_GRPC_BACKEND_SOURCE_PATH}/robot.pb.cc
        ${WEB_SERVER_HEADERS}
)

target_include_directories(
        ${PROJECT_NAME}_lib
        PUBLIC  include
        src
        ${PROTOBUF_INCLUDE_DIR}
        ${GENERATED_GRPC_BACKEND_SOURCE_PATH}
)

target_link_libraries(
        ${PROJECT_NAME}_lib
        PUBLIC utils_lib
        ${_GRPC_GRPCPP}
        ${_REFLECTION}
        ${_PROTOBUF_LIBPROTOBUF}
        Threads::Threads
)