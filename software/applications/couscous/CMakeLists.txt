cmake_minimum_required (VERSION 3.0)
project(couscous_app
        VERSION 1.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

file(GLOB_RECURSE HEADERS include/**.h src/**.h)

list(APPEND SOURCES
        src/main.cpp
        src/CouscousManager.cpp
)

add_executable(${PROJECT_NAME}_exe 
        ${SOURCES}
        ${HEADERS}
)

target_include_directories(
        ${PROJECT_NAME}_exe
        PUBLIC include
        PRIVATE src
)

target_link_libraries(${PROJECT_NAME}_exe
        PUBLIC utils_lib
               hali_lib
               posi_lib
               webserver_lib     
               navi_lib
               moti_lib
               missi_lib
)