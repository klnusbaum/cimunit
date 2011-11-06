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
    /// Mutex to synchronize operations on the schedule object
    cimunit_mutex_t mutex;
    
    /// List of events involved in the schedule
    cimunit_event_list_t *event_list;
    
    /// Structure containing the status of fired events
    cimunit_event_table_t fired_event_list;

    ///Table used for thread lookups
    cimunit_thread_table_t thread_table;
    
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
                                    const char *action_event);


/// Create a new schedule object
///
/// \return new schedule object
cimunit_schedule_t *cimunit_schedule_init();


/// Destroy the schedule object and free memory
void cimunit_schedule_destroy(cimunit_schedule_t *schedule);


/// Add a new event into the schedule
///
/// \param schedule - schedule associated with the test
/// \param name - name of the event to be added
/// \return pointer to the event object
cimunit_event_t *cimunit_schedule_add_event(struct cimunit_schedule *schedule,
                                            const char *name);


void cimunit_schedule_add_action_event(struct cimunit_schedule *schedule,
                                       const char *conditionEventName,
                                       const char *actionEventName);


/// Fire an event using the schedule
///
/// \param schedule - schedule associated with the event
/// \param eventName - name of the event to be fired_event_list
/// \return true if the event was found, else false
bool cimunit_schedule_fire(struct cimunit_schedule *schedule,
                           const char *eventName);


/// Get the thread name associated with the cimunit_thread_t
///
/// \param schedule - schedule associated with the name list
/// \param thread - thread whose name is being set
/// \param threadName - pointer to the name of the thread
void cimunit_schedule_set_thread_name(cimunit_schedule_t *schedule,
                                      cimunit_thread_t thread,
                                      const char *threadName);


/// Get the thread name associated with the cimunit_thread_t
///
/// \param schedule - schedule associated with the name list
/// \param thread - thread whose name is being queried
/// \return pointer to the name of the thread
const char *cimunit_schedule_get_thread_name(cimunit_schedule_t *schedule,
                                             cimunit_thread_t thread);


#endif //CIMUNIT_SCHEDULE_H
