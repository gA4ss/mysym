cmake_minimum_required (VERSION 3.5)
project(mysym VERSION 1.0)

# -g allows for gdb debugging
# turn on -03 for best performance
# add_definitions(-std=c++11 -g -O0 -DDEBUG -Wunused-variable)
# add_definitions(-std=c++11 -g -O0 -DDEBUG -Wunused-variable)
set(DEBUG TRUE)
if(DEBUG)
message(STATUS "compile debug version.")
add_definitions(-std=c++11 -g -O0 -DDEBUG -Wunused-variable)
else()
message(STATUS "compile release version.")
add_definitions(-std=c++11 -O3 -Wunused-variable)
endif(DEBUG)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

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
  ${SRC_DIRECTORY}/symopt.h
  ${SRC_DIRECTORY}/compile.h
  ${SRC_DIRECTORY}/exception.h
  ${SRC_DIRECTORY}/debug.h
)

#
# Mysym operator sources
#
set(MYSYM_OPERATOR_SRC
  ${SRC_DIRECTORY}/operator/abs.cc
  ${SRC_DIRECTORY}/operator/minus.cc
  ${SRC_DIRECTORY}/operator/add.cc
  ${SRC_DIRECTORY}/operator/sub.cc
  ${SRC_DIRECTORY}/operator/mul.cc
  ${SRC_DIRECTORY}/operator/div.cc
  ${SRC_DIRECTORY}/operator/mod.cc
  ${SRC_DIRECTORY}/operator/sqrt.cc
  ${SRC_DIRECTORY}/operator/pow.cc
  ${SRC_DIRECTORY}/operator/log.cc
  ${SRC_DIRECTORY}/operator/fact.cc
  ${SRC_DIRECTORY}/operator/trigo.cc
  ${SRC_DIRECTORY}/operator/hyper.cc
  ${SRC_DIRECTORY}/operator/frac.cc
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
  ${SRC_DIRECTORY}/create.cc
  ${SRC_DIRECTORY}/copy.cc
  ${SRC_DIRECTORY}/coefficient.cc
  ${SRC_DIRECTORY}/make.cc
  ${SRC_DIRECTORY}/tree.cc
  ${SRC_DIRECTORY}/merge.cc
  ${SRC_DIRECTORY}/operand.cc
  ${SRC_DIRECTORY}/base.cc
  ${SRC_DIRECTORY}/exponent.cc
  ${SRC_DIRECTORY}/simplify.cc
  ${SRC_DIRECTORY}/map.cc
  ${SRC_DIRECTORY}/sort.cc
  ${SRC_DIRECTORY}/find.cc
  ${SRC_DIRECTORY}/match.cc
  ${SRC_DIRECTORY}/substitute.cc
  ${SRC_DIRECTORY}/expansion.cc
  ${SRC_DIRECTORY}/symopt.cc
  ${SRC_DIRECTORY}/factor.cc
  ${SRC_DIRECTORY}/fraction.cc
  ${SRC_DIRECTORY}/limit.cc
  ${SRC_DIRECTORY}/integral.cc
  ${SRC_DIRECTORY}/func.cc
  ${SRC_DIRECTORY}/constant.cc
  ${SRC_DIRECTORY}/library.cc
  ${SRC_DIRECTORY}/list.cc
  ${SRC_DIRECTORY}/solve.cc
  ${SRC_DIRECTORY}/rational.cc
  ${SRC_DIRECTORY}/variables.cc
  ${SRC_DIRECTORY}/monomial.cc
  ${SRC_DIRECTORY}/polynomial.cc
  ${SRC_DIRECTORY}/expression.cc
  ${SRC_DIRECTORY}/degree.cc
  ${SRC_DIRECTORY}/cmp.cc
  ${MYSYM_OPERATOR_SRC}
  ${MYSYM_INTERPRETER_SRC}
  ${MYSYM_DEBUG_SRC}
)
# target_link_libraries(${PROJECT_NAME} mynum mympf mympz my)
target_link_libraries(${PROJECT_NAME} mympf mympz my)

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
add_test(NAME test_cmp COMMAND test_cmp)
set_tests_properties(test_cmp PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
add_test(NAME test_sort COMMAND test_sort)
set_tests_properties(test_sort PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")


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