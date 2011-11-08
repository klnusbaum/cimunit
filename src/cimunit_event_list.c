/**
 * \file cimunit_event_list.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cimunit_event_list.h"


cimunit_event_list_t *cimunit_event_list_init() {
    return NULL;
}


void cimunit_event_list_destroy(cimunit_event_list_t **list) {
    cimunit_event_list_t *event_entry_to_delete;
    cimunit_event_list_t *next_event_entry = *list;
    
    while (NULL != next_event_entry) {
        event_entry_to_delete = next_event_entry;
        next_event_entry = next_event_entry->next;
        free(event_entry_to_delete);
    }
    
    *list = NULL;
}


void cimunit_event_list_add(cimunit_event_list_t **list, cimunit_event_t *event) {
    cimunit_event_list_t *new_entry = malloc(sizeof(cimunit_event_list_t));

    // Insert new entry at the head of the list
    new_entry->event = event;
    new_entry->next = *list;
    *list = new_entry;
}


void cimunit_event_list_union(cimunit_event_list_t **list, cimunit_event_list_t *list2) {
    cimunit_event_list_t *data = list2;
    while (data != NULL) {
        if (NULL == cimunit_event_list_find(*list, data->event->event_name)) {
            cimunit_event_list_add(list, data->event);
        }
        data = data->next;
    }
}


cimunit_event_t *cimunit_event_list_find_with_thread(
  cimunit_event_list_t *list, const char *name, const char *thread) {
    cimunit_event_list_t *entry = list;
    // If no thread was provided, any event with the specified name will match
    if (NULL == thread) {
        while (NULL != entry) {
            if ((NULL == entry->event->thread_name) &&
                (strcmp(name, entry->event->event_name) == 0)) {
                return entry->event;
            }
            entry = entry->next;
        }
    } else {
        // Find event with matching thread name
        while (entry != NULL) {
            if ((strcmp(name, entry->event->event_name) == 0) &&
                (NULL != entry->event->thread_name)) {
                if (strcmp(thread, entry->event->thread_name) == 0) {
                    return entry->event;
                }
            }
            entry = entry->next;
        }
    }    
    return NULL;
}


cimunit_event_t *cimunit_event_list_find(cimunit_event_list_t *list,
                                         const char *name) {
    return cimunit_event_list_find_with_thread(list, name, NULL);
}
