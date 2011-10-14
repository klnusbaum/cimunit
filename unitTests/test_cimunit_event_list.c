/*
 * \file test_cimunit_event_list.c
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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "CUnit.h"

#include "cimunit_event_list.h"


static void test_cimunit_init_event_list(void)
{
    CU_ASSERT_PTR_NULL(cimunit_event_list_init());
}


static void test_cimunit_add_event_list(void)
{
    cimunit_event_list_t *list = NULL;
    cimunit_event_t *event = cimunit_event_init("a");
    
    cimunit_event_list_add(&list, event);
    CU_ASSERT_PTR_NOT_NULL(list);
    CU_ASSERT_PTR_EQUAL(list->event, event);
    
    cimunit_event_list_destroy(&list);
    CU_ASSERT_PTR_NULL(list);
}


static CU_TestInfo tests_cimunit_event[] = {
  {"init", test_cimunit_init_event_list},
  {"add event", test_cimunit_add_event_list},
  CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  {"suite_cimunit_event", NULL, NULL, tests_cimunit_event},
  CU_SUITE_INFO_NULL,
};

void AddEventListTests(void)
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

