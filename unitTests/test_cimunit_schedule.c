/*
 * \file test_cimunit_schedule.c
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

#include "testMain.h"
#include "cimunit_schedule.h"

static void test_cimunit_schedule_init(void)
{
    cimunit_schedule_t *schedule = cimunit_schedule_init(); 
    CU_ASSERT_PTR_NULL(schedule->event_list);
}


static void test_cimunit_schedule_parse_single(void)
{
    cimunit_schedule_t *schedule = cimunit_schedule_parse("a->x");
    CU_ASSERT_PTR_NOT_NULL_FATAL(schedule->event_list);
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(schedule->event_list, "x"));
    
    cimunit_event_t *action = cimunit_event_list_find(schedule->event_list, "a");
    CU_ASSERT_PTR_NOT_NULL_FATAL(action);
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(action->action_events, "x"));
}

static void test_cimunit_schedule_parse_double(void)
{
    cimunit_schedule_t *schedule = cimunit_schedule_parse("a->x,b->a");
    CU_ASSERT_PTR_NOT_NULL_FATAL(schedule->event_list);
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(schedule->event_list, "x"));
    
    cimunit_event_t *action = cimunit_event_list_find(schedule->event_list, "a");
    CU_ASSERT_PTR_NOT_NULL_FATAL(action);
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(action->action_events, "x"));

    action = cimunit_event_list_find(schedule->event_list, "b");
    CU_ASSERT_PTR_NOT_NULL_FATAL(action);
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(action->action_events, "a"));
}

static CU_TestInfo tests_cimunit_schedule[] = {
  {"init", test_cimunit_schedule_init},
  {"parse_single", test_cimunit_schedule_parse_single},
  {"parse_double", test_cimunit_schedule_parse_double},
  CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  {"suite_cimunit_schedule", NULL, NULL, tests_cimunit_schedule},
  CU_SUITE_INFO_NULL,
};

void AddScheduleTests(void)
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

RUN_TEST_SUITE(AddScheduleTests())
