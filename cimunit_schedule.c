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
#include "cimunit_schedule.h"

size_t getNumEvents(const char* string);
int getEventNames(char** events, const char *sched_string, int numEvents);

int cimunit_init_schedule(
  cimunit_schedule *cs, 
  const char *sched_string, 
  CIMUNIT_THREAD_AMOUNT numThreads)
{
  size_t i;
  cs->numThreads = numThreads;
  cs->sched_string = sched_string;

  size_t numEvents = getNumEvents(sched_string);
  char **events = (char**)malloc(sizeof(char*)*numEvents);
  getEventNames(events, sched_string, numEvents);

  cimunit_event_map *event_map =
    (cimunit_event_map*)malloc(sizeof(cimunit_event_map));
  cimunit_init_event_map(event_map, events, numEvents);
  
  free(events);
}

int cimunit_destroy_schedule(cimunit_schedule *cs){
  cimunit_destroy_event_map(cs->event_map);
  free(cs->event_map);
}

size_t getNumEvents(const char* string){
  size_t numEvents =0;
  char *toTokenize = (char*)malloc(sizeof(char)*strlen(string));
  strncpy(toTokenize, string, strlen(string));
  char *currentTok;
  currentTok = strtok(toTokenize, "->,");
  while(currentTok != NULL){
    ++numEvents;
    currentTok = strtok(NULL, "->,");
  } 
  return numEvents;
}

