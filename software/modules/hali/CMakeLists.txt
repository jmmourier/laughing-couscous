project(hali 
        VERSION 1.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

file(GLOB_RECURSE HEADERS include/**.h src/**.h test/**.h)

list(APPEND SOURCES 
    src/Serial.cpp
    src/MessageParser.cpp
    src/CommandInterpreter.cpp
    src/HalReal.cpp
    src/HalSimu.cpp
    src/serialib.cpp
    )

list(APPEND TESTS
    test/main.cpp
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
    ${Boost_INCLUDE_DIRS}
    PRIVATE
    src
)

target_link_libraries(${PROJECT_NAME}_lib ${Boost_LIBRARIES})


# Tests Binaries
add_executable(hali_test ${TESTS})
target_link_libraries(hali_test ${PROJECT_NAME}_lib)

