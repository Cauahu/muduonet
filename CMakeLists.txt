
#=====compile apollo_inf.so library======
cmake_minimum_required(VERSION 2.8)
project(apollo)

set(PROJECT_VERSION_MAJOR 0) #lib major version number
set(PROJECT_VERSION_MINOR 0) #lib minor version number
set(PROJECT_VERSION_PATCH 1) #lib patch patch version number

MESSAGE(STATUS "Try to make all the pathes from abs ")
set(WAIMAI_DIR "${PROJECT_SOURCE_DIR}/..")
MESSAGE(STATUS "uniform waimai dir : " ${WAIMAI_DIR})

#===== set project path =====
SET(ABS_PROJECT_SOURCE_DIR "${WAIMAI_DIR}/muduonet")
MESSAGE(STATUS "ABS_PROJECT_SOURCE_DIR is " ${ABS_PROJECT_SOURCE_DIR})

#===== set cmake path =====
SET(CMAKE_PATH "${WAIMAI_DIR}/muduonet/cmake")
MESSAGE(STATUS "CMAKE_PATH is " ${CMAKE_PATH})

#===== set include path =====
SET(PROJECT_INCLUDE_PATH "${WAIMAI_DIR}/muduonet/include")
MESSAGE(STATUS "PROJECT_INCLUDE_PATH is " ${PROJECT_INCLUDE_PATH})

#===== set source path =====
SET(PROJECT_SRC_PATH "${WAIMAI_DIR}/muduonet/src")
MESSAGE(STATUS "PROJECT_SRC_PATH is " ${PROJECT_SRC_PATH})

# all params about program's info like PORJECT_VERSION etc write into file named version.h.in 
# that all develper can use it instead of every one write this by themself
#configure_file("${PROJECT_INCLUDE_PATH}/base/version.h.in" "${PROJECT_INCLUDE_PATH}/base/version.h")

#import compiler config
include(${CMAKE_PATH}/compiler.cmake)
include(${CMAKE_PATH}/modules/Findgtest.cmake)

#import head file directory
include_directories(${PROJECT_INCLUDE_PATH})

#include all source files
file(GLOB_RECURSE MUDUONET_SROUCE_FILE ${PROJECT_SRC_PATH}/*.cc)

include_directories(${BOOST_INCLUDE_DIR})
#compile apollo shared library
add_library(muduonet SHARED ${MUDUONET_SROUCE_FILE})
