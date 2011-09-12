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
#ifdef CIMUNIT_EVENT_MAP_H
#define CIMUNIT_EVENT_MAP_H
#include "cimunit_event.h"
typedef struct{
  cimunit_event* event_array;
  size_t size;
} cimunit_event_map;

int cimunit_init_event_map(
  cimunit_event_map *to_init, 
  char** events, 
  size_t size);
int cimunit_destroy_event_map(cimunit_event_map *to_destroy);
int cimunit_find_event(
  cimunit_event_map* map, 
  const char* name, 
  cimunit_event *found_event);
#endif //CIMUNIT_EVENT_MAP_
