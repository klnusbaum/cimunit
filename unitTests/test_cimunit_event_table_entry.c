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

static void test_cimunit_event_table_entry_init(void){
  cimunit_event_t event;
  cimunit_event_init(&event, "a");
  cimunit_event_table_entry_t table_entry;
  cimunit_event_table_entry_init(&table_entry, &event);

  CU_ASSERT_PTR_NULL(table_entry.next); 
  CU_ASSERT_EQUAL(table_entry.event, &event);
  CU_ASSERT_EQUAL(cimunit_thread_self(), table_entry.thread);

  cimunit_event_table_entry_destroy(&table_entry);
  cimunit_event_destroy(&event);
}

static CU_TestInfo tests_cimunit_event_table_entry[] = {
  {"init", test_cimunit_event_table_entry_init},
  CU_TEST_INFO_NULL,
};

static CU_SuiteInfo suites[] = {
  {"suite_cimunit_event_table_entry", NULL, NULL, tests_cimunit_event_table_entry}, 
  CU_SUITE_INFO_NULL,
};

void AddEventTableEntryTests(void){
  assert(NULL != CU_get_registry());
  assert(!CU_is_test_running());

	/* Register suites. */
	if (CU_register_suites(suites) != CUE_SUCCESS) {
		fprintf(stderr, "suite registration failed - %s\n",
			CU_get_error_msg());
		exit(EXIT_FAILURE);
	}
}

RUN_TEST_SUITE(AddEventTableEntryTests())
