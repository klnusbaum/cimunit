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

int cimunit_get_schedule_event(
  const char *event_name,
  cimunit_schedule *schedule,
  cimunit_event *found_event)
{
  int i;
  for(i=0; i<schedule->numEvents; ++i){
    if(strcmp(event_name, schedule->events[i]->event_name) ==0){
      found_event = schedule->events[i];
      return 0;
    }
  }
  return 1;
}

int cimunit_init_schedule(
  cimunit_schedule *cs, 
  const char *sched_string, 
  CIMUNIT_THREAD_AMOUNT numThreads)
{
  size_t i;
  cs->numThreads = numThreads;
  cs->sched_string = sched_string;
  getNumEvents(sched_string, cs->numEvents);
  cs->events = (event**)malloc(sizeof(cimunit_event*)*(cs->numEvents));

  char **event_names = (char**)malloc(sizeof(char*)*cs->numEvents);
  getEventNames(event_names, sched_string, cs->numEvents);

  for(i=0; i<size; ++i){
    cimunit_event *toAdd = (cimunit_event*)malloc(sizeof(cimunit_event));
    cimunit_init_event(toAdd, events[i]);
    cs->events[i] = toAdd;
  }

  for(i=0; i<size; ++i){
    free(event_names[i]);
  }
  free(event_names); 
}

int cimunit_destroy_schedule(cimunit_schedule *cs){
  int i;
  for(i=0; i<cs->numEvents; ++i){
    free(events[i]);
  }
  free(events);
}

int getNumEvents(const char* string, size_t &numEvents){
  numEvents =0;
  char *toTokenize = (char*)malloc(sizeof(char)*strlen(string));
  strncpy(toTokenize, string, strlen(string));
  char *currentTok;
  currentTok = strtok(toTokenize, "->,");
  while(currentTok != NULL){
    ++numEvents;
    currentTok = strtok(NULL, "->,");
  } 
}

