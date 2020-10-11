cmake_minimum_required(VERSION 3.10)

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR arm)

# Set boost custom path for arm compiled version
set(Boost_INSTALL ${CMAKE_CURRENT_LIST_DIR}/external/boost/stage)
set(Boost_INCLUDE_DIR ${Boost_INSTALL}/include)
set(Boost_LIBRARY_DIRS ${Boost_INSTALL}/lib )
set(Boost_USE_STATIC_LIBS ON)

# Set arm compilator path
SET(PI_TOOLS_PATH ${CMAKE_CURRENT_LIST_DIR}/external/tools/arm-bcm2708)
set(CMAKE_SYSROOT ${PI_TOOLS_PATH}/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot)
set(CMAKE_C_COMPILER ${PI_TOOLS_PATH}/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${PI_TOOLS_PATH}/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++)

# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)