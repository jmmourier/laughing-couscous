cmake_minimum_required (VERSION 3.0)
project(application_test_gui
        VERSION 1.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")


file(GLOB_RECURSE HEADERS include/**.h src/**.h)

list(APPEND SOURCES
        src/main.cpp
        src/CouscousManager.cpp
)
        
# Tests Binaries
add_executable(${PROJECT_NAME}_exe ${SOURCES})

target_include_directories(
        ${PROJECT_NAME}_exe
        PUBLIC include
        PRIVATE src
)

target_link_libraries(${PROJECT_NAME}_exe
        PUBLIC webserver posi_lib
)