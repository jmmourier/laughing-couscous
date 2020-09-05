project(couscous_hali 
        VERSION 1.0
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Boost 
            1.65.1 #version
            REQUIRED #crash if not found 
            COMPONENTS system
            )

file(GLOB_RECURSE HEADERS include/**.h src/**.h test/**.h)

list(APPEND SOURCES 
    test/main.cpp
    src/Serial.cpp
    src/MessageParser.cpp)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} .) 
    add_executable(hali_example_exe ${SOURCES})
    target_link_libraries(hali_example_exe ${Boost_LIBRARIES})

elseif()
    message("Boost not found, skip executable")
endif()

