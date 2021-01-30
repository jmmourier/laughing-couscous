project(couscous_manager 
        VERSION 1.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

file(GLOB_RECURSE HEADERS include/**.h)

list(APPEND SOURCES 
    src/CouscousManager.cpp
    )

list(APPEND SOURCES_GUI
    src/CouscousManagerGui.cpp
    )

# Library
add_library(
    ${PROJECT_NAME}_lib
    STATIC ${SOURCES}
    ${HEADERS}
)

add_library(
    ${PROJECT_NAME}_gui_lib
    STATIC ${SOURCES_GUI}
    ${HEADERS}
)

target_include_directories(
    ${PROJECT_NAME}_lib
    PUBLIC include
    PRIVATE src
)

target_include_directories(
    ${PROJECT_NAME}_gui_lib
    PUBLIC include
    PRIVATE src
)

target_link_libraries(${PROJECT_NAME}_lib
    PUBLIC posi_lib
           hali_lib
)

target_link_libraries(${PROJECT_NAME}_gui_lib
    PUBLIC webserver 
           posi_lib
           hali_lib
)