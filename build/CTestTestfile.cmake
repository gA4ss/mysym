# CMake generated Testfile for 
# Source directory: /mnt/e/workspace/mysym
# Build directory: /mnt/e/workspace/mysym/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_basic "/mnt/e/workspace/mysym/build/test/test_basic")
set_tests_properties(test_basic PROPERTIES  FAIL_REGULAR_EXPRESSION "FAILED")
add_test(test_map "/mnt/e/workspace/mysym/build/test/test_map")
set_tests_properties(test_map PROPERTIES  FAIL_REGULAR_EXPRESSION "FAILED")
add_test(test_simplify "/mnt/e/workspace/mysym/build/test/test_simplify")
set_tests_properties(test_simplify PROPERTIES  FAIL_REGULAR_EXPRESSION "FAILED")
add_test(test_monomial "/mnt/e/workspace/mysym/build/test/test_monomial")
set_tests_properties(test_monomial PROPERTIES  FAIL_REGULAR_EXPRESSION "FAILED")
add_test(test_polynomial "/mnt/e/workspace/mysym/build/test/test_polynomial")
set_tests_properties(test_polynomial PROPERTIES  FAIL_REGULAR_EXPRESSION "FAILED")
add_test(test_fraction "/mnt/e/workspace/mysym/build/test/test_fraction")
set_tests_properties(test_fraction PROPERTIES  FAIL_REGULAR_EXPRESSION "FAILED")
add_test(test_expression "/mnt/e/workspace/mysym/build/test/test_expression")
set_tests_properties(test_expression PROPERTIES  FAIL_REGULAR_EXPRESSION "FAILED")
add_test(test_list "/mnt/e/workspace/mysym/build/test/test_list")
set_tests_properties(test_list PROPERTIES  FAIL_REGULAR_EXPRESSION "FAILED")
add_test(test_term "/mnt/e/workspace/mysym/build/test/test_term")
set_tests_properties(test_term PROPERTIES  FAIL_REGULAR_EXPRESSION "FAILED")
add_test(test_exponent "/mnt/e/workspace/mysym/build/test/test_exponent")
set_tests_properties(test_exponent PROPERTIES  FAIL_REGULAR_EXPRESSION "FAILED")
add_test(test_cmp "/mnt/e/workspace/mysym/build/test/test_cmp")
set_tests_properties(test_cmp PROPERTIES  FAIL_REGULAR_EXPRESSION "FAILED")
add_test(test_sort "/mnt/e/workspace/mysym/build/test/test_sort")
set_tests_properties(test_sort PROPERTIES  FAIL_REGULAR_EXPRESSION "FAILED")
add_test(test_match "/mnt/e/workspace/mysym/build/test/test_match")
set_tests_properties(test_match PROPERTIES  FAIL_REGULAR_EXPRESSION "FAILED")
subdirs("test")
