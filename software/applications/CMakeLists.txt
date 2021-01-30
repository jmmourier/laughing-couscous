cmake_minimum_required (VERSION 3.0)
project(applications)

if(ENABLE_GUI)
    add_subdirectory(application_1)
    add_subdirectory(application_integration)
endif()

add_subdirectory(application_gui_simulator)