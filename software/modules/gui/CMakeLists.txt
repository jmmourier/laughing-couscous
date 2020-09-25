cmake_minimum_required (VERSION 3.0)

##configuration for boost
project (simple-websocket-server)
add_compile_options(-std=c++11 -Wall -Wextra -Wsign-conversion)
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE ${CMAKE_THREAD_LIBS_INIT})

find_package(Boost 1.54.0 COMPONENTS system thread coroutine context REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE ${Boost_LIBRARIES})
target_include_directories(${PROJECT_NAME} INTERFACE ${Boost_INCLUDE_DIR})

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
    target_compile_definitions(${PROJECT_NAME} INTERFACE USE_BOOST_REGEX)
    find_package(Boost 1.54.0 COMPONENTS regex REQUIRED)
    target_link_libraries(${PROJECT_NAME} INTERFACE ${Boost_LIBRARIES})
    target_include_directories(${PROJECT_NAME} INTERFACE ${Boost_INCLUDE_DIR})
endif()

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE ${OPENSSL_LIBRARIES})
target_include_directories(${PROJECT_NAME} INTERFACE ${OPENSSL_INCLUDE_DIR})

## project
#[[

list(APPEND SOURCES
        src/webInterface/web_ws.cpp
        src/webInterface/messages_handler.cpp
        )

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        include
        PRIVATE
        src
        ${Boost_INCLUDE_DIRS} #a enlever
        ${Boost_INCLUDE_DIR}
)
]]
set(SRCS
       # src/main.cpp
        src/webInterface/web_ws.cpp
        src/webInterface/messages_handler.cpp
        )

set(HEADERS
        src/webInterface/messages_handler.h
        )

add_library(robotwebui ${SRCS} ${HEADERS})
target_include_directories(robotwebui  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(robotwebui simple-websocket-server)
target_link_libraries(robotwebui hali_lib)

find_package(Boost 1.54.0 COMPONENTS system thread filesystem REQUIRED)
target_link_libraries(robotwebui ${Boost_LIBRARIES})
target_include_directories(robotwebui PRIVATE ${Boost_INCLUDE_DIR})

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

add_executable(web_server_exe src/main.cpp)
target_link_libraries(web_server_exe webserver)