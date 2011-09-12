/**
 * Copyright 2011 Kurtis L. Nusbaum
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
#include "cimunit_event.h"

int cimunit_init_event(
  cimunit_event* to_init, 
  const char *name, 
  cimunit_event **depEvents,
  size_t numDepEvents)
{
  to_init->event_name = name;
  to_init->dep_events = depEvents;
  to_init->numDepEvents = numDepEvents;
  cimunit_mutex_init(&(to_init->mutex), NULL);
  cimunit_cond_init(&(to_init->condition), NULL);
}

int cimunit_destroy_event(cimunit_event* to_destroy){
  cimunit_mutex_destroy(&(to_destroy->mutex));
  cimunit_condition_destroy(&(to_destroy->condition));
}

int cimunit_fire_event(cimunit_event *event){
  size_t i;
  for(i=0; i<event->numDepEvents;++i){
    cimunit_cond_wait(
      event->depEvents[i]->condition, 
      event->depEvents[i]->mutex);
  }
  cimunit_cond_broadcast(event->condition);
}

