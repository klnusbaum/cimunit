/**
 * \file cimunit_event_list.c
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
#include <stdlib.h>

#include "cimunit_event_list.h"


cimunit_event_list_t *cimunit_event_list_init() {
    return NULL;
}


void cimunit_event_list_destroy(cimunit_event_list_t **list) {
    cimunit_event_list_t *event_to_delete;
    cimunit_event_list_t *next_event = *list;
    
    while (NULL != next_event) {
        event_to_delete = next_event;
        next_event = next_event->next;
        free(event_to_delete);
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


cimunit_event_t *cimunit_event_list_find(cimunit_event_list_t *list, char *name) {
    return NULL;
}