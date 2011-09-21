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

#ifndef CIMUNIT_EVENT_H
#define CIMUNIT_EVENT_H
#include "cimunit_mutex.h"

typedef struct cimunit_event{
  char *event_name;
  cimunit_mutex_t mutex; 
  struct cimunit_event **dep_events;  
  size_t numDepEvents;
} cimunit_event_t;

int cimunit_init_event(cimunit_event_t* to_init, char *name);
int cimunit_destroy_event(cimunit_event_t* to_destroy);
int cimunit_set_dependent_events(
  cimunit_event_t *event,
  cimunit_event_t **depEvents,
  size_t numDepEvents);
int cimunit_fire_event(cimunit_event_t *event);
#endif // CIMUNIT_EVENT_H
