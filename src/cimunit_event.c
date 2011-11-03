/**
 * \file cimunit_event.c
 *
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

#include <stdio.h>
#include <stdlib.h>

#include "cimunit_event.h"
#include "cimunit_event_list.h"


void cimunit_event_init(cimunit_event_t *event, const char *name)
{
    event->event_name = name;
    event->action_events = cimunit_event_list_init();
    cimunit_barrier_init(&(event->condition_barrier));

    event->is_action = false;
}


void cimunit_event_destroy(cimunit_event_t *event) {
    cimunit_event_list_destroy(&event->action_events); 
    cimunit_barrier_destroy(&(event->condition_barrier));
}


void cimunit_event_add_action(cimunit_event_t *condition,
                              cimunit_event_t *action)
{
    // Add event to head of the action event list
    cimunit_event_list_add(&condition->action_events, action);
    
    // action event now needs to be marked as such
    action->is_action = true;
}


const struct cimunit_event_list *cimunit_event_get_action_list(
  cimunit_event_t *event) {
    return event->action_events;
}
