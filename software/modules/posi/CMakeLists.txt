project(posi 
        VERSION 1.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

file(GLOB_RECURSE HEADERS include/**.h src/**.h test/**.h)

list(APPEND SOURCES 
    src/Posi.cpp
    )

list(APPEND TESTS
    test/PosiTest.cpp
    )

# Library
add_library(
    ${PROJECT_NAME}_lib
    STATIC ${SOURCES}
    ${HEADERS}
)

target_include_directories(
    ${PROJECT_NAME}_lib
    PUBLIC include
    PRIVATE src
)
    
target_link_libraries(${PROJECT_NAME}_lib 
    PUBLIC utils_lib
           logger_lib
           spdlog::spdlog
)

# Tests Binaries
add_executable(${PROJECT_NAME}_test ${TESTS})
target_include_directories(
    ${PROJECT_NAME}_test
    PUBLIC include
    PRIVATE src
    )
    
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib gtest_main logger_lib spdlog::spdlog)