cmake_minimum_required (VERSION 3.5)
project(mysym VERSION 1.0)

set(DEBUG TRUE)
if(DEBUG)
message(STATUS "compile debug version.")
add_definitions(-std=c++14 -g -O0 -DDEBUG -Wunused-variable)
else()
message(STATUS "compile release version.")
add_definitions(-std=c++14 -O3 -Wunused-variable)
endif(DEBUG)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# Sub modules directories
#
set(SRC_DIRECTORY ./src)

#
# Mympz include path
#
include_directories(
  ./
)

#
# System include path and link path
#
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

#
# Mysym public header file
#
set(MYSYM_HEADERS
  ${SRC_DIRECTORY}/mysym.h
  ${SRC_DIRECTORY}/symbol.h
  ${SRC_DIRECTORY}/compile.h
  ${SRC_DIRECTORY}/exception.h
  ${SRC_DIRECTORY}/debug.h
  ${SRC_DIRECTORY}/set.hpp
  ${SRC_DIRECTORY}/construct.h
)

#
# Mysym operator sources
#
set(MYSYM_OPERATOR_SRC
  ${SRC_DIRECTORY}/operator/cmp.cc
  ${SRC_DIRECTORY}/operator/atom.cc
  ${SRC_DIRECTORY}/operator/abs.cc
  ${SRC_DIRECTORY}/operator/add.cc
  ${SRC_DIRECTORY}/operator/sub.cc
  ${SRC_DIRECTORY}/operator/mul.cc
  ${SRC_DIRECTORY}/operator/div.cc
  ${SRC_DIRECTORY}/operator/mod.cc
  ${SRC_DIRECTORY}/operator/pow.cc
  ${SRC_DIRECTORY}/operator/log.cc
  ${SRC_DIRECTORY}/operator/fact.cc
  ${SRC_DIRECTORY}/operator/frac.cc
  ${SRC_DIRECTORY}/operator/logic/lnot.cc
  ${SRC_DIRECTORY}/operator/logic/land.cc
  ${SRC_DIRECTORY}/operator/logic/lor.cc
  ${SRC_DIRECTORY}/operator/equ/equ.cc
  ${SRC_DIRECTORY}/operator/equ/neq.cc
  ${SRC_DIRECTORY}/operator/equ/lt.cc
  ${SRC_DIRECTORY}/operator/equ/gt.cc
  ${SRC_DIRECTORY}/operator/equ/le.cc
  ${SRC_DIRECTORY}/operator/equ/ge.cc
  ${SRC_DIRECTORY}/operator/trigo/sin.cc
  ${SRC_DIRECTORY}/operator/trigo/cos.cc
  ${SRC_DIRECTORY}/operator/trigo/tan.cc
  ${SRC_DIRECTORY}/operator/trigo/cot.cc
  ${SRC_DIRECTORY}/operator/trigo/sec.cc
  ${SRC_DIRECTORY}/operator/trigo/csc.cc
  ${SRC_DIRECTORY}/operator/trigo/arcsin.cc
  ${SRC_DIRECTORY}/operator/trigo/arccos.cc
  ${SRC_DIRECTORY}/operator/trigo/arctan.cc
  ${SRC_DIRECTORY}/operator/trigo/arccot.cc
  ${SRC_DIRECTORY}/operator/trigo/arcsec.cc
  ${SRC_DIRECTORY}/operator/trigo/arccsc.cc
  ${SRC_DIRECTORY}/operator/hyper/sinh.cc
  ${SRC_DIRECTORY}/operator/hyper/cosh.cc
  ${SRC_DIRECTORY}/operator/hyper/tanh.cc
  ${SRC_DIRECTORY}/operator/hyper/coth.cc
  ${SRC_DIRECTORY}/operator/hyper/sech.cc
  ${SRC_DIRECTORY}/operator/hyper/csch.cc
  ${SRC_DIRECTORY}/operator/hyper/arcsinh.cc
  ${SRC_DIRECTORY}/operator/hyper/arccosh.cc
  ${SRC_DIRECTORY}/operator/hyper/arctanh.cc
  ${SRC_DIRECTORY}/operator/hyper/arccoth.cc
  ${SRC_DIRECTORY}/operator/hyper/arcsech.cc
  ${SRC_DIRECTORY}/operator/hyper/arccsch.cc
)

#
# Mysym interpreter sources
#
set(MYSYM_INTERPRETER_SRC
  ${SRC_DIRECTORY}/interpreter/interpreter.cc
)

#
# Debug sources
#
set(MYSYM_DEBUG_SRC
  ${SRC_DIRECTORY}/print.cc
)

#
# Library Build
#
add_library(${PROJECT_NAME} STATIC
  ${SRC_DIRECTORY}/mysym.cc
  ${SRC_DIRECTORY}/symbol.cc
  ${SRC_DIRECTORY}/create.cc
  ${SRC_DIRECTORY}/copy.cc
  ${SRC_DIRECTORY}/coefficient.cc
  ${SRC_DIRECTORY}/prime.cc
  ${SRC_DIRECTORY}/make.cc
  ${SRC_DIRECTORY}/tree.cc
  ${SRC_DIRECTORY}/operand.cc
  ${SRC_DIRECTORY}/base.cc
  ${SRC_DIRECTORY}/exponent.cc
  ${SRC_DIRECTORY}/term.cc
  ${SRC_DIRECTORY}/merge.cc
  ${SRC_DIRECTORY}/simplify.cc
  ${SRC_DIRECTORY}/map.cc
  ${SRC_DIRECTORY}/iteration.cc
  ${SRC_DIRECTORY}/sort.cc
  ${SRC_DIRECTORY}/find.cc
  ${SRC_DIRECTORY}/match.cc
  ${SRC_DIRECTORY}/pattern.cc
  ${SRC_DIRECTORY}/substitute.cc
  ${SRC_DIRECTORY}/expansion.cc
  ${SRC_DIRECTORY}/symopt.cc
  ${SRC_DIRECTORY}/basic_rule.cc
  ${SRC_DIRECTORY}/rule.cc
  ${SRC_DIRECTORY}/optinv.cc
  ${SRC_DIRECTORY}/optset.cc
  ${SRC_DIRECTORY}/optcase.cc
  ${SRC_DIRECTORY}/gcd.cc
  ${SRC_DIRECTORY}/lcm.cc
  ${SRC_DIRECTORY}/extend_euclid.cc
  ${SRC_DIRECTORY}/factor.cc
  ${SRC_DIRECTORY}/fraction.cc
  ${SRC_DIRECTORY}/limit.cc
  ${SRC_DIRECTORY}/integral.cc
  ${SRC_DIRECTORY}/constant.cc
  ${SRC_DIRECTORY}/library.cc
  ${SRC_DIRECTORY}/operator.cc
  ${SRC_DIRECTORY}/list.cc
  ${SRC_DIRECTORY}/solve.cc
  ${SRC_DIRECTORY}/units.cc
  ${SRC_DIRECTORY}/monomial.cc
  ${SRC_DIRECTORY}/polynomial.cc
  ${SRC_DIRECTORY}/elements.cc
  ${SRC_DIRECTORY}/sign.cc
  ${SRC_DIRECTORY}/degree.cc
  ${SRC_DIRECTORY}/compare.cc
  ${SRC_DIRECTORY}/global.cc
  ${SRC_DIRECTORY}/init.cc
  ${SRC_DIRECTORY}/misc.cc
  ${SRC_DIRECTORY}/number.cc
  ${SRC_DIRECTORY}/equation.cc
  ${SRC_DIRECTORY}/inequation.cc
  ${SRC_DIRECTORY}/expression.cc
  ${SRC_DIRECTORY}/wrapper.cc
  ${MYSYM_OPERATOR_SRC}
  ${MYSYM_INTERPRETER_SRC}
  ${MYSYM_DEBUG_SRC}
)
# target_link_libraries(${PROJECT_NAME} mynum mympf mympz my)
target_link_libraries(${PROJECT_NAME} mynum mympf mympz my)

#
# Test Build
#
set(BUILD_TEST TRUE)
if(BUILD_TEST)

#
# Add SubDirectory
#
add_subdirectory(test)

#
# Enable Test
#
enable_testing()
add_test(NAME test_basic COMMAND test_basic)
set_tests_properties(test_basic PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_map COMMAND test_map)
set_tests_properties(test_map PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_simplify COMMAND test_simplify)
set_tests_properties(test_simplify PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_monomial COMMAND test_monomial)
set_tests_properties(test_monomial PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_polynomial COMMAND test_polynomial)
set_tests_properties(test_polynomial PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_fraction COMMAND test_fraction)
set_tests_properties(test_fraction PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_expression COMMAND test_expression)
set_tests_properties(test_expression PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_list COMMAND test_list)
set_tests_properties(test_list PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_term COMMAND test_term)
set_tests_properties(test_term PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_exponent COMMAND test_exponent)
set_tests_properties(test_exponent PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_sort COMMAND test_sort)
set_tests_properties(test_sort PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_match COMMAND test_match)
set_tests_properties(test_match PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_elements COMMAND test_elements)
set_tests_properties(test_elements PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_sign COMMAND test_sign)
set_tests_properties(test_sign PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_degree COMMAND test_degree)
set_tests_properties(test_degree PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_coefficient COMMAND test_coefficient)
set_tests_properties(test_coefficient PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_symopt COMMAND test_symopt)
set_tests_properties(test_symopt PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_optset COMMAND test_optset)
set_tests_properties(test_optset PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_optcase COMMAND test_optcase)
set_tests_properties(test_optcase PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_rule COMMAND test_rule)
set_tests_properties(test_rule PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_units COMMAND test_units)
set_tests_properties(test_units PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_symbol COMMAND test_symbol)
set_tests_properties(test_symbol PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_factor COMMAND test_factor)
set_tests_properties(test_factor PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
# add_test(NAME test_io COMMAND test_io)
# set_tests_properties(test_io PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
# Test Operator
add_test(NAME test_cmp COMMAND test_cmp)
set_tests_properties(test_cmp PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_add COMMAND test_add)
set_tests_properties(test_add PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_mul COMMAND test_mul)
set_tests_properties(test_mul PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_div COMMAND test_div)
set_tests_properties(test_div PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_abs COMMAND test_abs)
set_tests_properties(test_abs PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_pow COMMAND test_pow)
set_tests_properties(test_pow PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
#
# Auto Test
#
set(BUILD_AUTOTEST FALSE)
if(BUILD_AUTOTEST)
endif(BUILD_AUTOTEST)

endif(BUILD_TEST)

#
# Install Set
#
INSTALL(TARGETS mysym ARCHIVE DESTINATION lib)
INSTALL(FILES ${MYSYM_HEADERS} DESTINATION include/mysym)