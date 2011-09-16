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
#include <stdlib.h>
#include <string.h>
#include "cimunit_schedule.h"
#include <stdio.h>

int getNumEvents(const char *string, size_t *numEvents){
  (*numEvents) =0;
  char *toTokenize = (char*)malloc(sizeof(char)*strlen(string));
  strncpy(toTokenize, string, strlen(string));
  char *currentTok;
  currentTok = strtok(toTokenize, "->,");
  while(currentTok != NULL){
    ++(*numEvents);
    currentTok = strtok(NULL, "->,");
  } 
}

int getEventNames(char **events, const char *sched_string, int numEvents){
  //TODO, ensure that i ends up at numEvents when currentTok is null.
  int i;
  i=0;
  char *toTokenize = (char*)malloc(sizeof(char)*strlen(sched_string));
  strncpy(toTokenize, sched_string, strlen(sched_string));
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

int cimunit_get_schedule_event(
  const char *event_name,
  const cimunit_schedule_t *schedule,
  cimunit_event_t **found_event)
{
  int i;
  for(i=0; i<schedule->numEvents; ++i){
    if(strcmp(event_name, schedule->events[i]->event_name) ==0){
      (*found_event) = schedule->events[i];
      return 0;
    }
  }
  return 1;
}

/*
int cimunit_create_schedule_events(cimunit_schedule_t *cs)
{
  char *toTokenize = (char*)malloc(sizeof(char)*strlen(cs->sched_string));
  strncpy(toTokenize, sched_string, strlen(cs->sched_string));
  char *currentTok;
  currentTok = strtok(toTokenize, "->,");

  cs->events = 
    (cimunit_event_t**)malloc(sizeof(cimunit_event_t*)*(cs->numEvents));

  for(int i=0; i<cs->numEvents; ++i){
    cimunit_event_t *toAdd = (cimunit_event_t*)malloc(sizeof(cimunit_event_t));
    cimunit_init_event(toAdd, currentTok);
    cs->events[i] = toAdd;
    currentTok = strtok(NULL, "->,");
  } 
}*/

int cimunit_init_schedule(
  cimunit_schedule_t *cs, 
  const char *sched_string, 
  cimunit_thread_amount_t numThreads)
{
  size_t i;
  cs->numThreads = numThreads;
  cs->sched_string = sched_string;

  getNumEvents(sched_string, &(cs->numEvents));

  //Replace this hardcode with actual parsing of the schedule.
  cs->events = 
    (cimunit_event_t**)malloc(sizeof(cimunit_event_t*)*(cs->numEvents));
  cs->events[0] = (cimunit_event_t*)malloc(sizeof(cimunit_event_t));
  cs->events[1] = (cimunit_event_t*)malloc(sizeof(cimunit_event_t));
  cimunit_init_event(cs->events[0], "t1begin");
  cimunit_init_event(cs->events[1], "t2end");
  

  //STATIC ASSIGNMENT OF DEPENECIES THIS IS JUST FOR TESTING OUT MY SAMPLE
  //PROGRAM!!!!
/*  cimunit_event_t *begin = NULL;
  cimunit_event_t *end = NULL;
  cimunit_get_schedule_event("t2begin", cs, &begin);
  cimunit_get_schedule_event("t1end", cs, &end);*/



  cimunit_event_t** begin_deps = 
    (cimunit_event_t**)malloc(sizeof(cimunit_event_t*));
  begin_deps[0] = cs->events[1];
  cimunit_set_dependent_events(cs->events[0], begin_deps, 1);
}

int cimunit_destroy_schedule(cimunit_schedule_t *cs){
  int i;
  for(i=0; i<cs->numEvents; ++i){
    free(cs->events[i]->dep_events);
    free(cs->events[i]);
  }
  free(cs->events);
  free(cs->event_names);
}

