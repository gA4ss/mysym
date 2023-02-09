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
subdirs("test")
