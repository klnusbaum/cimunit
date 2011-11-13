#ifndef TEST_MAIN_H
#define TEST_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CUnit.h"
#include "TestDB.h"

typedef enum {
  CU_BRM_NORMAL = 0,
  CU_BRM_SILENT,
  CU_BRM_VERBOSE
} CU_BasicRunMode;

CU_EXPORT CU_ErrorCode CU_basic_run_tests(void);

CU_EXPORT CU_ErrorCode CU_basic_run_suite(CU_pSuite pSuite);

CU_EXPORT CU_ErrorCode CU_basic_run_test(CU_pSuite pSuite, CU_pTest pTest);

CU_EXPORT void CU_basic_set_mode(CU_BasicRunMode mode);

CU_EXPORT CU_BasicRunMode CU_basic_get_mode(void);

CU_EXPORT void CU_basic_show_failures(CU_pFailureRecord pFailure);

void print_example_results(void);

void processArgs(
  int argc, 
  char* argv[], 
  CU_BasicRunMode *mode,
  CU_ErrorAction *error_action);

void cimunit_register_test_suites(CU_SuiteInfo suites[]);

#if defined(PLATFORM_Darwin) || \
    defined(PLATFORM_Linux)
  #define RUN_TEST_SUITE_PROTOTYPE(ENTRY) \
    int main(int argc, char* argv[])
#elif PLATFORM_VxWorks
  #define RUN_TEST_SUITE_PROTOTYPE(ENTRY) \
    int main(int argc, char* argv[])
#endif

#define RUN_TEST_SUITES( SUITES, ENTRY ) \
RUN_TEST_SUITE_PROTOTYPE(ENTRY) \
{ \
  CU_BasicRunMode mode = CU_BRM_NORMAL; \
  CU_ErrorAction error_action = CUEA_ABORT; \
  int failures = -1; \
 \
  setvbuf(stdout, NULL, _IONBF, 0); \
  processArgs(argc, argv, &mode, &error_action);  \
 \
  if (CU_initialize_registry()) { \
    printf("\nInitialization of Test Registry failed."); \
  } \
  else { \
    cimunit_register_test_suites( SUITES ); \
    CU_basic_set_mode(mode); \
    CU_set_error_action(error_action); \
    printf("\nTest run completed with return value %d.\n", CU_basic_run_tests()); \
    failures = CU_get_number_of_tests_failed(); \
    CU_cleanup_registry(); \
  } \
 \
  return failures; \
}


#endif
