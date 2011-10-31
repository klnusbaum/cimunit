/*
 *  CUnit - A Unit testing framework library for C.
 *  Copyright (C) 2001        Anil Kumar
 *  Copyright (C) 2004, 2005  Anil Kumar, Jerry St.Clair
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
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "testMain.h"
//#include "ExampleTests.h"

/* WARNING - MAINTENANCE NIGHTMARE AHEAD
 *
 * If you change any of the tests & suites below, you also need 
 * to keep track of changes in the result statistics and reflect
 * any changes in the result report counts in print_example_results().
 *
 * Yes, this could have been designed better using a more 
 * automated mechanism.  No, it was not done that way.  
 */

/* Suite initialization/cleanup functions */
static int suite_success_init(void) { return 0; }
static int suite_success_clean(void) { return 0; }

static void testSuccess1(void) { CU_ASSERT(1); }
static void testSuccess2(void) { CU_ASSERT(2); }
static void testSuccess3(void) { CU_ASSERT(3); }

/* Test functions for CUnit assertions */
static void testSimpleAssert(void)
{
  CU_ASSERT(1);
  CU_ASSERT(!0);
  CU_TEST(1);
}


static CU_TestInfo tests_success[] = {
  { "testSuccess1", testSuccess1 },
  { "testSuccess2", testSuccess2 },
  { "testSuccess3", testSuccess3 },
	CU_TEST_INFO_NULL,
};

static CU_TestInfo tests_simple[] = {
  { "testSimpleAssert", testSimpleAssert },
	CU_TEST_INFO_NULL,
};



static CU_SuiteInfo suites[] = {
  { "suite_success_both",  suite_success_init, suite_success_clean, tests_success },
  { "suite_success_init",  suite_success_init, NULL,                tests_success },
  { "suite_success_clean", NULL,               suite_success_clean, tests_success },
  { "TestSimpleAssert",    NULL,               NULL,                tests_simple },
	CU_SUITE_INFO_NULL,
};

void AddTests(void)
{
  assert(NULL != CU_get_registry());
  assert(!CU_is_test_running());

	/* Register suites. */
	if (CU_register_suites(suites) != CUE_SUCCESS) {
		fprintf(stderr, "suite registration failed - %s\n",
			CU_get_error_msg());
		exit(EXIT_FAILURE);
	}
}

RUN_TEST_SUITE(AddTests())
