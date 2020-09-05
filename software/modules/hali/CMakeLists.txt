project(couscous_module_hali 
        VERSION 1.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Boost 
            1.65.1 #version
            REQUIRED #crash if not found 
            COMPONENTS system
            )

file(GLOB_RECURSE HEADERS include/**.h src/**.h test/**.h)

list(APPEND SOURCES 
    src/Serial.cpp
    src/MessageParser.cpp
    src/CommandInterpreter.cpp
    src/Hali.cpp
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
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


# Tests Binaries
add_executable(hali_example_exe ${TESTS})
target_link_libraries(hali_example_exe ${PROJECT_NAME})

