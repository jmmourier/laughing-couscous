cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(couscous
        VERSION 1.0
        )

add_subdirectory(modules)
add_subdirectory(application)
add_subdirectory(external/grpc)