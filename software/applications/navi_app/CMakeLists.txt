cmake_minimum_required (VERSION 3.0)
project(nav_app
        VERSION 1.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")


file(GLOB_RECURSE HEADERS include/**.h src/**.h)

list(APPEND SOURCES
        src/main.cpp
        )

add_executable(${PROJECT_NAME}_exe  ${SOURCES} src/RobotController.cpp src/RobotController.h)

target_include_directories(
        ${PROJECT_NAME}_exe
        PUBLIC include
        PRIVATE src
)
# Tests Binaries

#target_link_libraries(application1_exe3 ${PROJECT_NAME})
target_link_libraries (${PROJECT_NAME}_exe
        LINK_PUBLIC
        hali_lib
        navi_lib
        posi_lib
        )