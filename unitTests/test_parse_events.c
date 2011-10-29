/*
 * \file test_parse_events.c
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

#include "cimunit_schedule.h"

static void test_parse_event_single(void)
{
    cimunit_schedule_t *schedule = cimunit_schedule_parse("a->x");

    CU_ASSERT_TRUE(cimunit_parse_schedule_runtime(schedule, "x"));

    CU_FAIL("parsing not yet happening");
}

static void test_parse_event_double(void)
{
    cimunit_schedule_t *schedule = cimunit_schedule_parse("a->x,b->a");
    
    CU_FAIL("parsing not yet happening");
}

static CU_TestInfo tests_parse_event_single[] = {
  {"parse_single", test_parse_event_single},
  {"parse_double", test_parse_event_double},
  CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  {"suite_parse_event_single", NULL, NULL, tests_parse_event_single},
  CU_SUITE_INFO_NULL,
};

void AddParseEventTests(void)
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

