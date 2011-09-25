/*
 * \file test_cimunit_event.c
 *
 * Copyright 2011 Dale Frampton
 * 
 * This file is part of cimunit.
 * 
 * cimunit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * cimunit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with cimunit.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "CUnit.h"

#include "cimunit_event.h"


static void test_cimunit_init_event(void) {
  cimunit_event_t event;
  char event_name[] = "test";
  
  cimunit_init_event(&event, event_name);
  
  /// - Verify the event name is initialized
  CU_ASSERT_PTR_NOT_NULL(event.event_name);
  CU_ASSERT_STRING_EQUAL(event.event_name, event_name);
  
  /// - No cross platform tests for mutex configuration
  
  /// - Verify the dependent events list is empty
  CU_ASSERT_PTR_NULL(event.dep_events);
}


static CU_TestInfo tests_cimunit_event[] = {
  { "init", test_cimunit_init_event },
	CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  { "suite_cimunit_event", NULL, NULL, tests_cimunit_event},
	CU_SUITE_INFO_NULL,
};

void AddEventTests(void)
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

