MESSAGE(STATUS "find gtest")

find_path(GTEST_INCLUDE_DIR gtest/gtest.h ${PROJECT_SOURCE_DIR}/..//bi_arch/third-64/gtest/output/include)
find_library(GTEST_LIBRARIES NAMES gtest PATHS ${PROJECT_SOURCE_DIR}/../bi_arch/third-64/gtest/output/lib)

#=====check whether gtest library exist=====
if (GTEST_INCLUDE_DIR AND GTEST_LIBRARIES)
    MESSAGE(STATUS "find gtest lib success")
else(GTEST_INCLUDE_DIR AND GTEST_LIBRARIES)
    MESSAGE(FATAL_ERROR "find gtest lib faild")
endif(GTEST_INCLUDE_DIR AND GTEST_LIBRARIES)

