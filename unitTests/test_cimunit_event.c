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
    char event_name[] = "test";

    cimunit_event_t *event = cimunit_event_init(event_name);
  
    /// - Verify the event name is initialized
    CU_ASSERT_PTR_NOT_NULL(event->event_name);
    CU_ASSERT_STRING_EQUAL(event->event_name, event_name);
    
    CU_ASSERT_FALSE(event->is_action);
  
    /// - No cross platform tests for mutex configuration
  
    /// - Verify the dependent events list is empty
    CU_ASSERT_PTR_NULL(event->dep_events);
    CU_ASSERT_PTR_NULL(event->action_events);
  
    cimunit_event_destroy(event);
}


static void test_cimunit_event_add_action(void) {
    cimunit_event_t *condition = cimunit_event_init("condition");
    cimunit_event_t *action = cimunit_event_init("action");
  
    /// - Run SUT
    cimunit_event_add_action(condition, action);
  
    /// - Verify the linked list is created properly;
    CU_ASSERT_PTR_NOT_NULL(condition->action_events);
    CU_ASSERT_PTR_NULL(condition->action_events->next_event);
    CU_ASSERT_PTR_EQUAL(condition->action_events->event,
                        action);
                        
    /// - Verify the action event is listed as an action event
    CU_ASSERT_TRUE(action->is_action);

    /// - Clean up
    cimunit_event_destroy(condition);
    cimunit_event_destroy(action);
}


static void test_cimunit_event_add_multiple_actions(void) {
    cimunit_event_t *condition = cimunit_event_init("condition");
    cimunit_event_t *action1 = cimunit_event_init("action1");
    cimunit_event_t *action2 = cimunit_event_init("action2");
    cimunit_event_add_action(condition, action1);
  
    /// - Run SUT
    cimunit_event_add_action(condition, action2);
  
    /// - Verify the linked list is created properly;
    cimunit_event_list_t *second_action =
      condition->action_events->next_event;

    /// - The first item should be action 2      
    CU_ASSERT_PTR_EQUAL(condition->action_events->event,
                        action2);

    /// - The second item should be action 1
    CU_ASSERT_PTR_NOT_NULL(second_action);
    CU_ASSERT_PTR_NULL(second_action->next_event);
    CU_ASSERT_PTR_EQUAL(condition->action_events->event,
                        action2);

    /// - Clean up
    cimunit_event_destroy(condition);
    cimunit_event_destroy(action1);
    cimunit_event_destroy(action2);
}



static CU_TestInfo tests_cimunit_event[] = {
  {"init", test_cimunit_init_event },
  {"add_action", test_cimunit_event_add_action},
  {"add_multiple_actions", test_cimunit_event_add_multiple_actions},
  CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  {"suite_cimunit_event", NULL, NULL, tests_cimunit_event},
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

