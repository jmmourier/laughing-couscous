cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
    endif ()

    set(CCACHE_BASEDIR ${CMAKE_SOURCE_DIR})
    set(CCACHE_NOHASHDIR Yes)

    message("INFO:\tccache found, using it !")

    set(CMAKE_C_COMPILER_LAUNCHER ccache)
    set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif ()

project(couscous
        VERSION 1.0
        )

add_subdirectory(modules)
add_subdirectory(applications)
#add_subdirectory(application_test_gui)
add_subdirectory(external/googletest)
