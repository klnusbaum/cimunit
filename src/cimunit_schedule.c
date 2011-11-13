/**
 * \file cimunit_schedule.c
 *
 * Copyright 2011 Dale Frampton and Kurtis Nusbaum
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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "cimunit_schedule.h"
#include "cimunit_thread.h"

cimunit_schedule_t *cimunit_schedule_init() {
    cimunit_schedule_t *schedule = malloc(sizeof(cimunit_schedule_t));
    cimunit_mutex_init(&schedule->mutex, NULL);
    cimunit_thread_table_init(&(schedule->thread_table)); 
    schedule->event_list = cimunit_event_list_init();
    cimunit_event_table_init(&schedule->fired_event_list, &(schedule->thread_table));
    schedule->schedule_string = NULL;

    return schedule;
}


void cimunit_schedule_destroy(cimunit_schedule_t *schedule) {
    cimunit_event_list_t *event_list = schedule->event_list;

    cimunit_thread_table_destroy(&(schedule->thread_table));
    
    while(event_list) {
        cimunit_event_destroy(event_list->event);
        event_list = event_list->next;
    }
    cimunit_event_list_destroy(&schedule->event_list);
    
    free(schedule->schedule_string);
}


BOOL cimunit_schedule_fire(struct cimunit_schedule *schedule,
                           const char *eventName)
{
    const char *thread_name;
    cimunit_event_t *event;
    const cimunit_event_list_t *next_action;

    thread_name = cimunit_schedule_get_thread_name(schedule,
                                                   cimunit_thread_self());

    event = cimunit_event_list_find_with_thread(schedule->event_list,
                                                eventName, thread_name); 
      
    if (!event) {
        event = cimunit_event_list_find(schedule->event_list, eventName);
    }
    if (event) {
        cimunit_add_event_to_table(&schedule->fired_event_list, event, NULL);

        next_action = cimunit_event_get_action_list(event);
      
        // When the event is fired, open the barriers associated with this event.
        // e.x.  a->b   fire_event('a') causes the barrier associated with 'b' to
        // be unlocked.
        while(next_action) {
            if (cimunit_schedule_parse_runtime(
                  schedule, next_action->event->event_name,
                  next_action->event->thread_name)) {
                cimunit_barrier_unlock(&(next_action->event->condition_barrier));
            }
            next_action = next_action->next;
        }
      
        if (event->is_action) {
            cimunit_barrier_wait(&(event->condition_barrier));
        }
    } else {
        return FALSE;
    }
    
    return TRUE;
}


void cimunit_schedule_set_thread_name(cimunit_schedule_t *schedule,
                                      cimunit_thread_t thread,
                                      const char *threadName)
{
    cimunit_mutex_lock(&schedule->mutex);
    cimunit_set_thread_name(&schedule->thread_table, thread, threadName);                                      
    cimunit_mutex_unlock(&schedule->mutex);
}


const char *cimunit_schedule_get_thread_name(cimunit_schedule_t *schedule,
                                             cimunit_thread_t thread)
{
    const char *thread_name;
    cimunit_get_thread_name(&schedule->thread_table, thread, &thread_name);

    return thread_name;
}
