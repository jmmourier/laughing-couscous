project(logger LANGUAGES CXX)

list(APPEND SOURCES
    src/LoggerFactory.cpp
)

file(GLOB_RECURSE HEADERS include/*.h)

add_compile_definitions(LOG_DIR="/tmp/")

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
    PUBLIC spdlog::spdlog
)