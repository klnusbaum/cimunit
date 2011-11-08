/**
 * \file cimunit_event.h
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

#ifndef CIMUNIT_EVENT_H
#define CIMUNIT_EVENT_H

#include <stdbool.h>

#include "cimunit_mutex.h"
#include "cimunit_barrier.h"

/// Forward declarations
struct cimunit_event_list;


/// Structure defining a CIMUnit event.
typedef struct cimunit_event {
    /// Textual name of the event, used by scheduling rules
    const char *event_name;
    
    /// Textual name of the thread, or NULL if not associated
    /// with a thread
    const char *thread_name;

    /// List of action events that wait on this condition event
    struct cimunit_event_list *action_events;
    
    /// Barrier associated with the event in case it is used as a
    /// condition event.
    cimunit_barrier_t condition_barrier;

    /// Is this event an action event?  If so, it may block when it is
    /// fired.  If not, it will not block.
    bool is_action;
} cimunit_event_t;


/// Create a new instance of a CIMUnit event that is associated with a thread
///
/// \param event - Event to initialize.
/// \param name - name of the event
/// \param thread - name of the thread
void cimunit_event_init_with_thread(cimunit_event_t *event, const char *name,
                                    const char *thread);


/// Create a new instance of a CIMUnit event not associated with a thread
///
/// \param event - Event to initialize.
/// \param name - name of the event
void cimunit_event_init(cimunit_event_t *event, const char *name);


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


/// Get the list of actions that depend on this event
///
/// \pram event - event whose action list is being retrieved
/// \return the list of action event dependent on this condition event
const struct cimunit_event_list *cimunit_event_get_action_list(
  cimunit_event_t *event);

#endif // CIMUNIT_EVENT_H
