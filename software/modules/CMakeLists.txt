cmake_minimum_required (VERSION 3.0)
project(modules)

if(ENABLE_GUI)
    add_subdirectory(gui)
endif()
add_subdirectory(hali)
add_subdirectory(moti)
add_subdirectory(posi)
