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
#include "cimunit_event_map.h"
int cimunit_init_event_map(
  cimunit_event_map *to_init, 
  char** events, 
  size_t size)
{
  size_t i;
  to_init->event_array = (cimunit_event**)malloc(sizeof(cimunit_event*)*size);
  for(i=0; i<size; ++i){
    cimunit_event *toAdd = (cimunit_event*)malloc(sizeof(cimunit_event));
    cimunit_init_event(toAdd, events[i]);
    to_init->event_array[i] = toAdd;
  }
}

int cimunit_destroy_event_map(cimunit_event_map *to_destroy){
  int i;
  for(i = 0; i<to_destroy->length; ++i){
    cimunit_destroy_event(to_destroy->event_array[i]);
    free(to_destroy->event_array[i]);
  }
  free(to_destroy->event_array);
}

int cimunit_find_event(
  cimunit_event_map* map, 
  const char* name, 
  cimunit_event *found_event)
{
  int i;
  for(i=0; i<map->length; ++i){
    if(map->event_array[i] != NULL &&
      strcmp(name, map->event_array[i]->event_name) ==0)
    {
      found_event = map->event_array[i];
      return 0;
    }
  }
  return 1;
}

