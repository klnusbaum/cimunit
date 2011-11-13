/*
 *  CUnit - A Unit testing framework library for C.
 *  Copyright (C) 2004  Anil Kumar, Jerry St.Clair
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
#include <stdio.h>
#include "testMain.h"
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif
void print_example_results(void)
{
  fprintf(stdout, "\n\nExpected Test Results:"
                  "\n\n  Error Handling  Type      # Run   # Pass   # Fail"
                  "\n\n  ignore errors   suites%9u%9u%9u"
                    "\n                  tests %9u%9u%9u"
                    "\n                  asserts%8u%9u%9u"
                  "\n\n  stop on error   suites%9u%9u%9u"
                    "\n                  tests %9u%9u%9u"
                    "\n                  asserts%8u%9u%9u\n\n",
                  14, 14, 3,
                  31, 10, 21,
                  89, 47, 42,
                  4, 4, 1,
                  12, 9, 3,
                  12, 9, 3);
}

void processArgs(
  int argc, 
  char* argv[], 
  CU_BasicRunMode *mode,
  CU_ErrorAction *error_action)
{
  int i;
  for (i=1 ; i<argc ; i++) { 
    if (!strcmp("-i", argv[i])) { 
      *error_action = CUEA_IGNORE; 
    } 
    else if (!strcmp("-f", argv[i])) { 
      *error_action = CUEA_FAIL; 
    } 
    else if (!strcmp("-A", argv[i])) { 
      *error_action = CUEA_ABORT; 
    } 
    else if (!strcmp("-s", argv[i])) { 
      *mode = CU_BRM_SILENT; 
    } 
    else if (!strcmp("-n", argv[i])) { 
      *mode = CU_BRM_NORMAL; 
    } 
    else if (!strcmp("-v", argv[i])) { 
      *mode = CU_BRM_VERBOSE; 
    } 
    else if (!strcmp("-e", argv[i])) { 
      print_example_results(); 
      return;
    } 
    else { 
      printf("\nUsage:  BasicTest [options]\n\n" 
               "Options:   -i   ignore framework errors [default].\n" 
               "           -f   fail on framework error.\n" 
               "           -A   abort on framework error.\n\n" 
               "           -s   silent mode - no output to screen.\n" 
               "           -n   normal mode - standard output to screen.\n" 
               "           -v   verbose mode - max output to screen [default].\n\n" 
               "           -e   print expected test results and exit.\n" 
               "           -h   print this message and exit.\n\n"); 
      return;
    } 
  } 
}
void cimunit_register_test_suites(CU_SuiteInfo suites[]){

  assert(NULL != CU_get_registry());
  assert(!CU_is_test_running());

	if (CU_register_suites(suites) != CUE_SUCCESS) {
		fprintf(stderr, "suite registration failed - %s\n",
			CU_get_error_msg());
		return;
	}

}

#ifdef __cplusplus
}
#endif
