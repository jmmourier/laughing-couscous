cmake_minimum_required(VERSION 3.10)

project(couscous_hali)

set(CMAKE_CXX_STANDARD 11)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.40.0 COMPONENTS system)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} .) 
    add_executable(hali_example main.cpp)
    target_link_libraries(hali_example ${Boost_LIBRARIES})
elseif()
    message("Boost not found, skip executable")
endif()

