project(moti
        VERSION 1.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

file(GLOB_RECURSE HEADERS include/**.h src/**.h test/**.h)

list(APPEND SOURCES 
    src/Moti.cpp
    )

list(APPEND TESTS
    test/main.cpp
    )

# Library
add_library(
    ${PROJECT_NAME}
    STATIC ${SOURCES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC 
    include
    PRIVATE
    src
)

# Tests Binaries
add_executable(moti_example_exe ${TESTS})
target_link_libraries(moti_example_exe ${PROJECT_NAME})

