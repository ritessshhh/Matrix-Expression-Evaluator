#include "unit_tests.h"

TestSuite(student_tests, .timeout = TEST_TIMEOUT);

Test(base_execute, add_mats01_new) { run_script_without_valgrind("script21"); }
Test(base_execute_valgrind, add_mats01_new) { expect_no_valgrind_errors(run_script_with_valgrind("script21")); }

Test(base_execute, add_mats02_new) { run_script_without_valgrind("script22"); }
Test(base_execute_valgrind, add_mats02_new) { expect_no_valgrind_errors(run_script_with_valgrind("script22")); }

Test(base_execute, add_mats03_new) { run_script_without_valgrind("script23"); }
Test(base_execute_valgrind, add_mats03_new) { expect_no_valgrind_errors(run_script_with_valgrind("script23")); }
