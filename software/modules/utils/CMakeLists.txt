project(utils
        VERSION 1.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE HEADERS include/**.h src/**.h test/**.h)

# Library
add_library(
    ${PROJECT_NAME}_lib
)

target_include_directories(
    ${PROJECT_NAME}_lib
    PUBLIC 
    include
)
