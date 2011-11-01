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
#include "testMain.h"
#include "cimunit.h"
#include <assert.h>

static void test_cimunit_event_table_init(void){
  cimunit_event_table_t event_table;
  cimunit_init_event_table(&event_table);
  CU_ASSERT_PTR_NULL(event_table.head); 
  CU_ASSERT_PTR_NULL(event_table.tail); 
  CU_ASSERT_EQUAL(0,cimunit_mutex_trylock(&(event_table.lock)));
  cimunit_mutex_unlock(&(event_table.lock));
  cimunit_destroy_event_table(&event_table);
}

static CU_TestInfo tests_cimunit_event_table[] = {
  {"init", test_cimunit_event_table_init},
  CU_TEST_INFO_NULL,
};

static CU_SuiteInfo suites[] = {
  {"suite_cimunit_event_table", NULL, NULL, tests_cimunit_event_table}, 
  CU_SUITE_INFO_NULL,
};

void AddEventTableTests(void){
  assert(NULL != CU_get_registry());
  assert(!CU_is_test_running());

	/* Register suites. */
	if (CU_register_suites(suites) != CUE_SUCCESS) {
		fprintf(stderr, "suite registration failed - %s\n",
			CU_get_error_msg());
		exit(EXIT_FAILURE);
	}
}

RUN_TEST_SUITE(AddEventTableTests())
