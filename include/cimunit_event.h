/**
 * \file cimunit_event.h
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

#ifndef CIMUNIT_EVENT_H
#define CIMUNIT_EVENT_H

#include <stdbool.h>

#include "cimunit_mutex.h"
#include "cimunit_barrier.h"

struct cimunit_event_list;


/// Structure defining a CIMUnit event.
typedef struct cimunit_event {
    /// Textual name of the event, used by scheduling rules
    char *event_name;

    /// List of action events that wait on this condition event
    struct cimunit_event_list *action_events;
    
    /// Barrier associated with the event in case it is used as a
    /// condition event.
    cimunit_barrier_t *condition_barrier;

    /// Is this event an action event?  If so, it may block when it is
    /// fired.  If not, it will not block.
    bool is_action;
    
  cimunit_mutex_t mutex;
  struct cimunit_event **dep_events;
  size_t numDepEvents;
  
} cimunit_event_t;


/// Create a new instance of a CIMUnit event
///
/// \param event - Event to initialize.
/// \param name - name of the event
/// \returns - 0 if the initilization was successful, error code otherwise.
int cimunit_event_init(cimunit_event_t *event, char *name);


/// Destroy a CIMUnit event and free its allocated memory.
///
/// \param event - event to be destroyed
void cimunit_event_destroy(cimunit_event_t *event);


/// Add an action event to be triggered by this condition event
///
/// \param condition - event that will trigger the action event
/// \param action - event that will be blocked until the condition
///                 is fired.
void cimunit_event_add_action(cimunit_event_t *condition,
                              cimunit_event_t *action);


/// Cause all action events associated with this event to trigger
///
/// \note This method will pend if this event is an action event of
///       a condition event that hasn't fired yet.
///
/// \param event - event whose condition events are being triggered
void cimunit_event_fire(cimunit_event_t *event);


/// Cause thread to wait on this event
///
/// \note This method will not trigger the fire event actions.  It just
///       pends on the event's barrier.
void cimunit_event_lock_and_wait(cimunit_event_t *event);




int cimunit_set_dependent_events(
    cimunit_event_t *event,
    cimunit_event_t **depEvents,
    size_t numDepEvents);

int cimunit_fire_event(cimunit_event_t *event);

#endif // CIMUNIT_EVENT_H
