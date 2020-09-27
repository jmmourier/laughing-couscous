project(navi
        VERSION 1.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Boost 
            1.65.1 #version
            REQUIRED #crash if not found 
            COMPONENTS system
            )

file(GLOB_RECURSE HEADERS include/**.h src/**.h )

list(APPEND SOURCES
        src/Navi.cpp
    )


# Library
add_library(
    ${PROJECT_NAME}_lib
    STATIC ${SOURCES}
)

target_include_directories(
    ${PROJECT_NAME}_lib
    PUBLIC 
    include
    PRIVATE
    src
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}_lib ${Boost_LIBRARIES})


# Tests Binaries
#target_link_libraries(Navi ${PROJECT_NAME}_lib)

