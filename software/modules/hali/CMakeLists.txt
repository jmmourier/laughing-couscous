cmake_minimum_required(VERSION 3.10)

project(couscous_hali 
        VERSION 1.0
        )

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 
            1.65.1 #version
            REQUIRED #crash if not found 
            COMPONENTS system
            )

list(APPEND SOURCES 
    main.cpp
    Serial.cpp
    MessageParser.cpp)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} .) 
    add_executable(hali_example_exe ${SOURCES})
    target_link_libraries(hali_example_exe ${Boost_LIBRARIES})

elseif()
    message("Boost not found, skip executable")
endif()

