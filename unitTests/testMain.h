/*
 *  CUnit - A Unit testing framework library for C.
 *  Copyright (C) 2004-2006  Jerry St.Clair
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 *  Interface for simple test runner.
 *
 *  11-Aug-2004   Initial implementation of basic test runner interface. (JDS)
 */

/** @file
 * Basic interface with output to stdout.
 */
/** @addtogroup Basic
 * @{
 */

#ifndef TEST_MAIN_H
#define TEST_MAIN_H

#include "CUnit.h"
#include "TestDB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

void print_example_results(void);

#define RUN_TEST_SUITE( SUITE ) \
int main(int argc, char* argv[]) \
{ \
  CU_BasicRunMode mode = CU_BRM_NORMAL; \
  CU_ErrorAction error_action = CUEA_ABORT; \
  int i; \
  int failures = -1; \
 \
  setvbuf(stdout, NULL, _IONBF, 0); \
 \
  for (i=1 ; i<argc ; i++) { \
    if (!strcmp("-i", argv[i])) { \
      error_action = CUEA_IGNORE; \
    } \
    else if (!strcmp("-f", argv[i])) { \
      error_action = CUEA_FAIL; \
    } \
    else if (!strcmp("-A", argv[i])) { \
      error_action = CUEA_ABORT; \
    } \
    else if (!strcmp("-s", argv[i])) { \
      mode = CU_BRM_SILENT; \
    } \
    else if (!strcmp("-n", argv[i])) { \
      mode = CU_BRM_NORMAL; \
    } \
    else if (!strcmp("-v", argv[i])) { \
      mode = CU_BRM_VERBOSE; \
    } \
    else if (!strcmp("-e", argv[i])) { \
      print_example_results(); \
      return 0; \
    } \
    else { \
      printf("\nUsage:  BasicTest [options]\n\n" \
               "Options:   -i   ignore framework errors [default].\n" \
               "           -f   fail on framework error.\n" \
               "           -A   abort on framework error.\n\n" \
               "           -s   silent mode - no output to screen.\n" \
               "           -n   normal mode - standard output to screen.\n" \
               "           -v   verbose mode - max output to screen [default].\n\n" \
               "           -e   print expected test results and exit.\n" \
               "           -h   print this message and exit.\n\n"); \
      return 0; \
    } \
  } \
 \
  if (CU_initialize_registry()) { \
    printf("\nInitialization of Test Registry failed."); \
  } \
  else { \
    SUITE; \
    CU_basic_set_mode(mode); \
    CU_set_error_action(error_action); \
    printf("\nTest run completed with return value %d.\n", CU_basic_run_tests()); \
    failures = CU_get_number_of_tests_failed(); \
    CU_cleanup_registry(); \
  } \
 \
  return failures; \
}




/** Run modes for the basic interface. */
typedef enum {
  CU_BRM_NORMAL = 0,  /**< Normal mode - failures and run summary are printed [default]. */
  CU_BRM_SILENT,      /**< Silent mode - no output is printed except framework error messages. */
  CU_BRM_VERBOSE      /**< Verbose mode - maximum output of run details. */
} CU_BasicRunMode;

CU_EXPORT CU_ErrorCode CU_basic_run_tests(void);
/**< 
 *  Runs all registered CUnit tests using the basic interface.
 *  The default CU_BasicRunMode is used unless it has been
 *  previously changed using CU_basic_set_mode().  The CUnit test
 *  registry must have been initialized before calling this function.
 *
 *  @return A CU_ErrorCode indicating the framework error condition, including
 *          CUE_NOREGISTRY - Registry has not been initialized.
 */

CU_EXPORT CU_ErrorCode CU_basic_run_suite(CU_pSuite pSuite);
/**< 
 *  Runs all tests for a specific suite in the basic interface.
 *  If pSuite is NULL, the function returns without taking any
 *  action. The default CU_BasicRunMode is used unless it has
 *  been changed using CU_basic_set_mode().
 *
 *  @param pSuite The CU_Suite to run.
 *  @return A CU_ErrorCode indicating the framework error condition, including
 *          CUE_NOSUITE - pSuite was NULL.
 */


CU_EXPORT CU_ErrorCode CU_basic_run_test(CU_pSuite pSuite, CU_pTest pTest);
/**<
 *  Runs a single test in a specific suite in the basic interface.
 *  If pSuite or pTest is NULL, the function returns without
 *  taking any action.  The default CU_BasicRunMode is used unless
 *  it has been changed using CU_basic_set_mode.
 *
 *  @param pSuite The CU_Suite holding the CU_Test to run.
 *  @param pTest  The CU_Test to run.
 *  @return A CU_ErrorCode indicating the framework error condition, including
 *          CUE_NOSUITE - pSuite was NULL.
 *          CUE_NOTEST  - pTest was NULL.
 */

CU_EXPORT void CU_basic_set_mode(CU_BasicRunMode mode);
/**< Sets the run mode for the basic interface.
 *  @param mode The new CU_BasicRunMode for subsequent test
 *              runs using the basic interface.
 */

CU_EXPORT CU_BasicRunMode CU_basic_get_mode(void);
/**< Retrieves the current run mode for the basic interface.
 *  @return The current CU_BasicRunMode setting for test
 *              runs using the basic interface.
 */

CU_EXPORT void CU_basic_show_failures(CU_pFailureRecord pFailure);
/**<
 *  Prints a summary of run failures to stdout.
 *  This is provided for user convenience upon request, and does 
 *  not take into account the current run mode.  The failures are 
 *  printed to stdout independent of the most recent run mode.
 *
 *  @param pFailure List of CU_pFailureRecord's to output.
 */

#ifdef __cplusplus
}
#endif
#endif  /*  TEST_MAIN_H  */
/** @} */
