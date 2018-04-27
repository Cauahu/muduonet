MESSAGE(STATUS "find benchmark")

find_path(BENCHMARK_INCLUDE_DIR benchmark/benchmark.h ${WAIMAI_DIR}/bi_public/benchmark/include)

find_library(BENCHMARK_LIBRARIES NAMES benchmark PATHS ${WAIMAI_DIR}/bi_public/benchmark/output/lib)

#=====check whether benchmark library exist=====
if (BENCHMARK_INCLUDE_DIR AND BENCHMARK_LIBRARIES)
    MESSAGE(STATUS "find BENCHMARK lib success")
else(BENCHMARK_INCLUDE_DIR AND BENCHMARK_LIBRARIES)
    MESSAGE(FATAL_ERROR "find BENCHMARK lib faild")
endif(BENCHMARK_INCLUDE_DIR AND BENCHMARK_LIBRARIES)
