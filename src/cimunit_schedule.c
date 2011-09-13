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
  cimunit_schedule_t *schedule,
  cimunit_event_t *found_event)
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
  cimunit_schedule_t *cs, 
  const char *sched_string, 
  cimunit_thread_amount numThreads)
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
    cimunit_init_event(toAdd, event_names[i]);
    cs->events[i] = toAdd;
  }

  //STATIC ASSIGNMENT OF DEPENECIES THIS IS JUST FOR TESTING OUT MY SAMPLE
  //PROGRAM!!!!
  cimunit_event_t *begin = NULL;
  cimunit_event_t *end = NULL;
  cimunit_get_schedule_event("t2begin", cs, begin);
  cimunit_get_schedule_event("t1end", cs, end);
  cimunit_even begin_deps[1];
  begin_deps[0] = end;
  cimunit_set_dependent_events(begin, begin_deps, 1);

  for(i=0; i<size; ++i){
    free(event_names[i]);
  }
  free(event_names); 
}

int cimunit_destroy_schedule(cimunit_schedule_t *cs){
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

int getEventNames(char** events, const char *sched_string, int numEvents){
  //TODO, ensure that i ends up at numEvents when currentTok is null.
  int i;
  i=0;
  char *toTokenize = (char*)malloc(sizeof(char)*strlen(string));
  strncpy(toTokenize, string, strlen(string));
  char *currentTok;
  currentTok = strtok(toTokenize, "->,");

  while(currentTok != NULL){
    size_t token_length = strlen(currentTok);
    char *copied_token = (char*)malloc(sizeof(char)*(token_length+1));
    strcpy(copied_token, currentTok);
    events[i++]= copied_token;
    currentTok = strtok(NULL, "->,");
  } 

}
