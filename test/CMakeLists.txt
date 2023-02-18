cmake_minimum_required (VERSION 3.5)
project(mysym_test VERSION 1.0)

# -g allows for gdb debugging
# turn on -03 for best performance
# add_definitions(-std=c++11 -g -O0 -Wunused-variable)
add_definitions(-std=c++11 -g -O0 -DDEBUG -Wunused-variable)
# add_definitions(-std=c++11 -O3 -Wunused-variable)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

#
# Sub modules directories
#
set(SRC_DIRECTORY .)

#
# Mympz include path
#
include_directories(
  ../src
)

#
# System include path and link path
#
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

#
# Main Test
#
add_executable(test_basic ${SRC_DIRECTORY}/test_basic.cc)
target_link_libraries(test_basic mysym gtest pthread)
add_executable(test_map ${SRC_DIRECTORY}/test_map.cc)
target_link_libraries(test_map mysym gtest pthread)
add_executable(test_simplify ${SRC_DIRECTORY}/test_simplify.cc)
target_link_libraries(test_simplify mysym gtest pthread)
add_executable(test_monomial ${SRC_DIRECTORY}/test_monomial.cc)
target_link_libraries(test_monomial mysym gtest pthread)
add_executable(test_polynomial ${SRC_DIRECTORY}/test_polynomial.cc)
target_link_libraries(test_polynomial mysym gtest pthread)
add_executable(test_fraction ${SRC_DIRECTORY}/test_fraction.cc)
target_link_libraries(test_fraction mysym gtest pthread)
add_executable(test_expression ${SRC_DIRECTORY}/test_expression.cc)
target_link_libraries(test_expression mysym gtest pthread)

# add_executable(test_addsub ${SRC_DIRECTORY}/test_addsub.cc)
# target_link_libraries(test_addsub mympf gtest pthread)
# add_executable(test_cmp ${SRC_DIRECTORY}/test_cmp.cc)
# target_link_libraries(test_cmp mympf gtest pthread)
# add_executable(test_mul ${SRC_DIRECTORY}/test_mul.cc)
# target_link_libraries(test_mul mympf gtest pthread)
# add_executable(test_exp ${SRC_DIRECTORY}/test_exp.cc)
# target_link_libraries(test_exp mympf gtest pthread)
# add_executable(test_div ${SRC_DIRECTORY}/test_div.cc)
# target_link_libraries(test_div mympf gtest pthread)
# add_executable(test_mod ${SRC_DIRECTORY}/test_mod.cc)
# target_link_libraries(test_mod mympf gtest pthread)

#
# Misc Test
#
# add_executable(test_misc ${SRC_DIRECTORY}/misc/test_misc.cc)
# target_link_libraries(test_misc mympf)