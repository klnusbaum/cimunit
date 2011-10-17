/**
 * \file cimunit_event_list.h
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

#ifndef CIMUNIT_EVENT_LIST_H
#define CIMUNIT_EVENT_LIST_H

#include <stdbool.h>

#include "cimunit_event.h"

/// Structure defining a CIMUnit event.
typedef struct cimunit_event_list {
    /// Pointer to event structure
    cimunit_event_t *event;

    /// Next event in the list
    struct cimunit_event_list *next;
} cimunit_event_list_t;


/// Create a new and empty instance of an event list
///
/// \returns - NULL.  It doesn't do much at this point, perhaps never.
cimunit_event_list_t *cimunit_event_list_init();

/// Cleans up the memory associated with the event list
///
/// \param list - event list to be cleaned up
void cimunit_event_list_destroy(cimunit_event_list_t **list);

/// Add a new event into the list
///
/// \param list - event list to be updated
/// \param event - event to be added into the list
void cimunit_event_list_add(cimunit_event_list_t **list, cimunit_event_t *event);


/// Gets an event from the list by namespace
///
/// \param list - event list being queried
/// \param name - name of the event being searched for
/// \return NULL if the event wasn't found, else a pointer to the event.
cimunit_event_t *cimunit_event_list_find(cimunit_event_list_t *list, char *name);

#endif // CIMUNIT_EVENT_LIST_H
