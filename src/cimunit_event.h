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


/// Structure defining a CIMUnit event.
typedef struct cimunit_event {
    /// Textual name of the event, used by scheduling rules
    char *event_name;

    /// List of events that wait on this event to be triggered
    struct cimunit_event_list *action_events;
    
    /// Is this event an action event?  If so, it may block when it is
    /// fired.  If not, it will not block.
    bool is_action;

  cimunit_mutex_t mutex;
  struct cimunit_event **dep_events;
  size_t numDepEvents;
  
} cimunit_event_t;


/// Linked list of all known events by name
typedef struct cimunit_event_list {
    /// Pointer to event record
    cimunit_event_t *event;
  
    /// Pointer to next record in the list.  Null if this is the last record.
    struct cimunit_event_list *next_event;
} cimunit_event_list_t;


/// Create a new instance of a CIMUnit event
///
/// \param - name of the event
/// \returns - a pointer to the event.  The pointer must be deallocated
///            by calling \sa cimunit_event_destroy
cimunit_event_t *cimunit_event_init(char *name);


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





int cimunit_set_dependent_events(
    cimunit_event_t *event,
    cimunit_event_t **depEvents,
    size_t numDepEvents);

int cimunit_fire_event(cimunit_event_t *event);

#endif // CIMUNIT_EVENT_H
