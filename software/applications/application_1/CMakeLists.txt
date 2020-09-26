cmake_minimum_required (VERSION 3.0)
project(application1
        VERSION 1.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Boost
        1.65.1 #version
        REQUIRED #crash if not found
        COMPONENTS system
        )

file(GLOB_RECURSE HEADERS include/**.h src/**.h)

list(APPEND SOURCES
        src/main.cpp
        )

# Library
add_library(
        ${PROJECT_NAME}
        STATIC ${SOURCES}
)

target_link_libraries (${PROJECT_NAME} LINK_PUBLIC robotwebui)
target_link_libraries (${PROJECT_NAME} LINK_PUBLIC hali_lib)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        src
        ${Boost_INCLUDE_DIRS}
)

# Tests Binaries
add_executable(application1_exe  ${SOURCES})
target_link_libraries(application1_exe ${PROJECT_NAME})
