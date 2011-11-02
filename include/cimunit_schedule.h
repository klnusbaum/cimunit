/**
 * Copyright 2011 Kurtis L. Nusbaum & Dale Frampton
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
#ifndef CIMUNIT_SCHEDULE_H
#define CIMUNIT_SCHEDULE_H

#include "cimunit_event.h"
#include "cimunit_event_list.h"
#include "cimunit_event_table.h"

typedef size_t cimunit_thread_amount_t;


/// Structure use to define a CIMUnit schedule
typedef struct cimunit_schedule {
    /// List of events involved in the schedule
    cimunit_event_list_t *event_list;
    
    /// Structure containing the status of fired events
    cimunit_event_table_t fired_event_list;
    
    /// Text version of the schedule
    char *schedule_string;
} cimunit_schedule_t;


/// Create a new schedule from the passed string
///
/// \param schedule_string - schedule to be met
/// \return newly created and configured schedule object
cimunit_schedule_t *cimunit_schedule_parse(char *schedule_string);


/// Checks if the action event is blocked
///
/// \param schedule - schedule associated with the test
/// \param action_event - action event being queried
/// \return true if event is blocked, else false
bool cimunit_schedule_parse_runtime(cimunit_schedule_t *schedule,
                                    char *action_event);


/// Create a new schedule object
///
/// \return new schedule object
cimunit_schedule_t *cimunit_schedule_init();


/// Destroy the schedule object and free memory
void cimunit_schedule_destroy(cimunit_schedule_t *schedule);


/// Fire an event using the schedule
///
/// \param schedule - schedule associated with the event
/// \param eventName - name of the event to be fired_event_list
/// \return true if the event was found, else false
bool cimunit_schedule_fire(struct cimunit_schedule *schedule, char *eventName);

#endif //CIMUNIT_SCHEDULE_H
