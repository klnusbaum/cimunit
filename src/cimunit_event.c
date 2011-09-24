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


cimunit_event_t *cimunit_event_init(char *name)
{
    cimunit_event_t *event = malloc(sizeof(cimunit_event_t));
  
    event->event_name = name;
    cimunit_mutex_init(&(event->mutex), NULL);
    cimunit_mutex_lock(&(event->mutex));
    event->dep_events = NULL;
    event->numDepEvents = 0;
    event->action_events = NULL;
    event->is_action = false;
  
    return event;
}


void cimunit_event_destroy(cimunit_event_t *event) {
    cimunit_event_list_t *list = event->action_events;
    event->action_events = NULL;
    
    cimunit_event_list_t *delete_list;
    
    while(list != NULL)
    {
      delete_list = list;
      list = list->next_event;
      
      // Clean-up
      cimunit_mutex_destroy(&(delete_list->event->mutex));
      free(delete_list);
    }
    
    free(event);
}


void cimunit_event_add_action(cimunit_event_t *condition,
                              cimunit_event_t *action)
{
    cimunit_event_list_t *new_action =
      malloc(sizeof(cimunit_event_list_t));
     
    // Add action to head of the action list
    new_action->event = action;
    new_action->next_event = condition->action_events;
    condition->action_events = new_action;
    
    // action event now need to be marked as such
    action->is_action = true;
}


void cimunit_event_fire(cimunit_event_t *event)
{
    cimunit_event_list_t *next_action = event->action_events;
  
    while (next_action != NULL)
    {
        cimunit_mutex_unlock(&(next_action->event->mutex));
    }
  
    if (event->is_action) {
        cimunit_mutex_lock(&(event->mutex));
    }
}

int cimunit_set_dependent_events(
  cimunit_event_t *event,
  cimunit_event_t **depEvents,
  size_t numDepEvents)
{
  if(event == NULL){
    fprintf(stderr, "Cannot assign dependent events to a NULL pointer\n");
    exit(1);
  }
  event->dep_events = depEvents;
  event->numDepEvents = numDepEvents;
}


int cimunit_fire_event(cimunit_event_t *event){
  size_t i;
  //printf(" trying to fire: %s \n", event->event_name);
  //ASSERT DEPEVENTS NOT NULL!!!!!!
  for(i=0; i<event->numDepEvents;++i){
    cimunit_mutex_lock(&(event->dep_events[i]->mutex));
    cimunit_mutex_unlock(&(event->dep_events[i]->mutex));
  }
  cimunit_mutex_unlock(&(event->mutex));
}

