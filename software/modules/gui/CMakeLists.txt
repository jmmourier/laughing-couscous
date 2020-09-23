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

