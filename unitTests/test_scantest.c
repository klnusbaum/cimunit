/**
 * \file scantest.c
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
#include "testMain.h"
#include "cimunit.h"
#include "cimunit_schedule.h"
#include "cimunit_event_list.h"


/// Display all conditions that are associated with the passed action
///
/// \param event - action event
static void printConditionsForActionEvent(cimunit_event_t *event) {
    cimunit_event_list_t *action_list = event->action_events;

    printf("%s has the following actions that wait on it\n", event->event_name);
    if (!action_list) {
        printf("\tnone\n");
    } else {
        while(action_list) {
            printf("\t%s\n", action_list->event->event_name);
            action_list = action_list->next;
        }
    }
}


static void test_scantest_func(void)
{

  cimunit_schedule_t *schedule = cimunit_schedule_parse("a->b,b->c");
	cimunit_event_list_t *condition_list = schedule->event_list;

	printf("Print the first schedule\n");
	while(condition_list != NULL) {
	    printConditionsForActionEvent(condition_list->event);
	    condition_list = condition_list->next;
	}	
	cimunit_schedule_destroy(schedule);
	
	schedule = cimunit_schedule_parse("d->e");
	printf("Print the second schedule\n");
	condition_list = schedule->event_list;
	while(condition_list != NULL) {
	    printConditionsForActionEvent(condition_list->event);
	    condition_list = condition_list->next;
	}
	cimunit_schedule_destroy(schedule);
}

static CU_TestInfo tests_scantest[] = {
  {"scantest", test_scantest_func},
  CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  {"scan test", NULL, NULL, tests_scantest},
  CU_SUITE_INFO_NULL,
};

RUN_TEST_SUITES(suites, test_scantest);
