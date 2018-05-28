cmake_minimum_required(VERSION 2.8)
project(apollo_test)

SET(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/..")
SET(ABS_PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}")

#===== set cmake module path =====
SET(CMAKE_MODULE_PATH ${CMAKE_ROOT}/MODULES ${PROJECT_SOURCE_DIR}/cmake/modules)
MESSAGE(STATUS "CMAKE_MODULE_PATH is " ${CMAKE_MODULE_PATH})

include(${PROJECT_SOURCE_DIR}/cmake/compiler.cmake)

#===== include src header =====
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/output/lib)

#===== compile gtest formatter file =====
SET(TEST_FILE_NAME "gtest_date")
find_package(gtest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
add_executable(${TEST_FILE_NAME} ${PROJECT_SOURCE_DIR}/test/${TEST_FILE_NAME}.cc)
target_link_libraries(${TEST_FILE_NAME} ${GTEST_LIBRARIES} muduonet pthread)
#===== compile gtest formatter file end =====

#===== compile gtest parser file =====
#find_package(gtest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIR})
#add_executable(gtest_numric_parser ${PROJECT_SOURCE_DIR}/test/format_test/gtest_numeric_parser.cc)
#target_link_libraries(gtest_numric_parser ${GTEST_LIBRARIES} apollo pthread)
##===== compile gtest parser file end =====
#
##===== compile benchmark formatter file =====
#find_package(benchmark REQUIRED)
#include_directories(${BENCHMARK_INCLUDE_DIR})
#add_executable(benchmark_formatter ${PROJECT_SOURCE_DIR}/test/format_test/benchmark_formatter.cc)
#target_link_libraries(benchmark_formatter ${BENCHMARK_LIBRARIES} apollo pthread)
##===== compile benchmark formatter file end =====
