cmake_minimum_required (VERSION 3.0)

project (Simple-WebSocket-Server)
add_compile_options(-std=c++11 -Wall -Wextra -Wsign-conversion)
add_library(simple-websocket-server INTERFACE)
target_include_directories(simple-websocket-server INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Threads REQUIRED)
target_link_libraries(simple-websocket-server INTERFACE ${CMAKE_THREAD_LIBS_INIT})

find_package(Boost 1.54.0 COMPONENTS system thread coroutine context REQUIRED)
target_link_libraries(simple-websocket-server INTERFACE ${Boost_LIBRARIES})
target_include_directories(simple-websocket-server INTERFACE ${Boost_INCLUDE_DIR})

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
    target_compile_definitions(simple-websocket-server INTERFACE USE_BOOST_REGEX)
    find_package(Boost 1.54.0 COMPONENTS regex REQUIRED)
    target_link_libraries(simple-websocket-server INTERFACE ${Boost_LIBRARIES})
    target_include_directories(simple-websocket-server INTERFACE ${Boost_INCLUDE_DIR})
endif()

find_package(OpenSSL REQUIRED)
target_link_libraries(simple-websocket-server INTERFACE ${OPENSSL_LIBRARIES})
target_include_directories(simple-websocket-server INTERFACE ${OPENSSL_INCLUDE_DIR})

add_executable(robotwebui src/main.cpp src/webInterface/web_ws.cpp src/webInterface/messages_handler.cpp src/webInterface/messages_handler.h)

target_link_libraries(robotwebui simple-websocket-server)
find_package(Boost 1.54.0 COMPONENTS system thread filesystem REQUIRED)
target_link_libraries(robotwebui ${Boost_LIBRARIES})
target_include_directories(robotwebui PRIVATE ${Boost_INCLUDE_DIR})