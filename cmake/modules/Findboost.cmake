MESSAGE(STATUS "find boost")


find_path(BOOST_INCLUDE_DIR boost/weak_ptr.hpp "${WAIMAI_DIR}/bi_arch/third-64/boost/output/include")
find_library(BOOST_LIBRARIES NAMES boost_log PATHS "${WAIMAI_DIR}/bi_arch/third-64/boost/output/lib")

#=====check whether gboost library exist=====
if (BOOST_INCLUDE_DIR AND BOOST_LIBRARIES)
    MESSAGE(STATUS "find boost lib success")
else(BOOST_INCLUDE_DIR AND BOOST_LIBRARIES)
    MESSAGE(FATAL_ERROR "find boost lib faild")
endif(BOOST_INCLUDE_DIR AND BOOST_LIBRARIES)

