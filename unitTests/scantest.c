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
#include "cimunit_schedule.h"

int main()
{

    cimunit_schedule_t *schedule = cimunit_schedule_parse("a->b,b->c");
	printf("Print the first schedule\n");
	cimunit_event_list_t *condition_list = schedule->event_list;
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
