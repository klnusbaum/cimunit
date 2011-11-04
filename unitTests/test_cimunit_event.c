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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cimunit.h"
#include "testMain.h"


static void test_cimunit_init_event(void)
{
    char event_name[] = "test";

    cimunit_event_t event;
    cimunit_event_init(&event, event_name);
  
    /// - Verify the event name is initialized
    CU_ASSERT_PTR_NOT_NULL(event.event_name);
    CU_ASSERT_STRING_EQUAL(event.event_name, event_name);
    
    /// - Verify the thread name isn't set
    CU_ASSERT_PTR_NULL(event.thread_name);
    
    CU_ASSERT_FALSE(event.is_action);
  
    /// - No cross platform tests for mutex configuration
  
    /// - Verify the dependent events list is empty
    CU_ASSERT_PTR_NULL(event.action_events);
  
    cimunit_event_destroy(&event);
}


static void test_cimunit_init_event_with_thread(void)
{
    char event_name[] = "test";
    char thread_name[] = "thread";

    cimunit_event_t event;
    cimunit_event_init_with_thread(&event, event_name, thread_name);
  
    /// - Verify the event name is initialized
    CU_ASSERT_PTR_NOT_NULL_FATAL(event.event_name);
    CU_ASSERT_STRING_EQUAL(event.event_name, event_name);

    /// - Verify the thread name is initialized
    CU_ASSERT_PTR_NOT_NULL_FATAL(event.thread_name);
    CU_ASSERT_STRING_EQUAL(event.thread_name, thread_name);
    
    CU_ASSERT_FALSE(event.is_action);
  
    /// - No cross platform tests for mutex configuration
  
    /// - Verify the dependent events list is empty
    CU_ASSERT_PTR_NULL(event.action_events);
  
    cimunit_event_destroy(&event);
}


static void test_cimunit_event_add_action(void)
{
    cimunit_event_t condition;
    cimunit_event_init(&condition, "condition");
    cimunit_event_t action;
    cimunit_event_init(&action, "action");
  
    /// - Run SUT
    cimunit_event_add_action(&condition, &action);
  
    /// - Verify the action is in the list
    CU_ASSERT_PTR_NOT_NULL(condition.action_events);
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(condition.action_events,
                                                   action.event_name));
                        
    /// - Verify the action event is listed as an action event
    CU_ASSERT_TRUE(action.is_action);

    /// - Clean up
    cimunit_event_destroy(&condition);
    cimunit_event_destroy(&action);
}


static void test_cimunit_event_add_multiple_actions(void)
{
    cimunit_event_t condition;
    cimunit_event_init(&condition, "condition");
    cimunit_event_t action1;
    cimunit_event_init(&action1, "action1");
    cimunit_event_t action2;
    cimunit_event_init(&action2, "action2");
    cimunit_event_add_action(&condition, &action1);
  
    /// - Run SUT
    cimunit_event_add_action(&condition, &action2);

    /// - Verify both items are in the list
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(condition.action_events,
                                                   action1.event_name));
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(condition.action_events,
                                                   action2.event_name));

    /// - Clean up
    cimunit_event_destroy(&condition);
    cimunit_event_destroy(&action1);
    cimunit_event_destroy(&action2);
}


static CU_TestInfo tests_cimunit_event[] = {
  {"init", test_cimunit_init_event},
  {"init with thread", test_cimunit_init_event_with_thread},
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

RUN_TEST_SUITE( AddEventTests() )

