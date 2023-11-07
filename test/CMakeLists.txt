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
add_executable(test_list ${SRC_DIRECTORY}/test_list.cc)
target_link_libraries(test_list mysym gtest pthread)
add_executable(test_term ${SRC_DIRECTORY}/test_term.cc)
target_link_libraries(test_term mysym gtest pthread)
add_executable(test_exponent ${SRC_DIRECTORY}/test_exponent.cc)
target_link_libraries(test_exponent mysym gtest pthread)
add_executable(test_sort ${SRC_DIRECTORY}/test_sort.cc)
target_link_libraries(test_sort mysym gtest pthread)
add_executable(test_match ${SRC_DIRECTORY}/test_match.cc)
target_link_libraries(test_match mysym gtest pthread)
add_executable(test_elements ${SRC_DIRECTORY}/test_elements.cc)
target_link_libraries(test_elements mysym gtest pthread)
add_executable(test_sign ${SRC_DIRECTORY}/test_sign.cc)
target_link_libraries(test_sign mysym gtest pthread)
add_executable(test_degree ${SRC_DIRECTORY}/test_degree.cc)
target_link_libraries(test_degree mysym gtest pthread)
add_executable(test_coefficient ${SRC_DIRECTORY}/test_coefficient.cc)
target_link_libraries(test_coefficient mysym gtest pthread)
add_executable(test_symopt ${SRC_DIRECTORY}/test_symopt.cc)
target_link_libraries(test_symopt mysym gtest pthread)
add_executable(test_optset ${SRC_DIRECTORY}/test_optset.cc)
target_link_libraries(test_optset mysym gtest pthread)
add_executable(test_optcase ${SRC_DIRECTORY}/test_optcase.cc)
target_link_libraries(test_optcase mysym gtest pthread)
add_executable(test_rule ${SRC_DIRECTORY}/test_rule.cc)
target_link_libraries(test_rule mysym gtest pthread)
add_executable(test_set ${SRC_DIRECTORY}/test_set.cc)
target_link_libraries(test_set my)
add_executable(test_units ${SRC_DIRECTORY}/test_units.cc)
target_link_libraries(test_units mysym gtest pthread)
add_executable(test_io ${SRC_DIRECTORY}/test_io.cc)
target_link_libraries(test_io mysym gtest pthread)
# Test Operator
add_executable(test_cmp ${SRC_DIRECTORY}/test_cmp.cc)
target_link_libraries(test_cmp mysym gtest pthread)
add_executable(test_add ${SRC_DIRECTORY}/test_add.cc)
target_link_libraries(test_add mysym gtest pthread)
add_executable(test_sub ${SRC_DIRECTORY}/test_sub.cc)
target_link_libraries(test_sub mysym gtest pthread)
add_executable(test_mul ${SRC_DIRECTORY}/test_mul.cc)
target_link_libraries(test_mul mysym gtest pthread)
add_executable(test_div ${SRC_DIRECTORY}/test_div.cc)
target_link_libraries(test_div mysym gtest pthread)
add_executable(test_abs ${SRC_DIRECTORY}/test_abs.cc)
target_link_libraries(test_abs mysym gtest pthread)
add_executable(test_pow ${SRC_DIRECTORY}/test_pow.cc)
target_link_libraries(test_pow mysym gtest pthread)
add_executable(test_symbol ${SRC_DIRECTORY}/test_symbol.cc)
target_link_libraries(test_symbol mysym gtest pthread)
# DO NOT add test cases
add_executable(test_misc ${SRC_DIRECTORY}/test_misc.cc)
target_link_libraries(test_misc mysym gtest pthread)

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