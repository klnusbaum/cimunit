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
  const char *name)
{
  to_init->event_name = name;
  cimunit_mutex_init(&(to_init->mutex), NULL);
  cimunit_mutex_lock(&(to_init->mutex));
}

int cimunit_destroy_event(cimunit_event* to_destroy){
  cimunit_mutex_destroy(&(to_destroy->mutex));
}

int cimunit_set_dependent_events(
  cimunit_event *event,
  cimunit_event **depEvents,
  size_t numDepEvents)
{
  event->dep_events = depEvents;
  event->numDepEvents = numDepEvents;
}

int cimunit_fire_event(cimunit_event *event){
  size_t i;
  //ASSERT DEPEVENTS NOT NULL!!!!!!
  for(i=0; i<event->numDepEvents;++i){
    cimunit_mutex_lock(&(event->depEvents[i]->mutex));
    cimunit_mutex_unlock(&(event->depEvents[i]->mutex));
  }
  cimunit_mutex_unlock(&(event->mutex));
}

