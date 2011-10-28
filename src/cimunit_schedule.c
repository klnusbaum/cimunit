/**
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
#include <stdlib.h>
#include <string.h>
#include "cimunit_schedule.h"
#include <stdio.h>


cimunit_schedule_t *cimunit_schedule_init() {
    cimunit_schedule_t *schedule = malloc(sizeof(cimunit_schedule_t));
    
    schedule->event_list = cimunit_event_list_init();
}


void cimunit_schedule_destroy(cimunit_schedule_t *schedule) {
    cimunit_event_list_t *event_list = schedule->event_list;
    
    while(event_list) {
        cimunit_event_destroy(event_list->event);
        event_list = event_list->next;
    }
    cimunit_event_list_destroy(&schedule->event_list);
}



int cimunit_get_num_events(const char *string, size_t *numEvents){
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
  (*found_event) = NULL;
  return 1;
}

int cimunit_init_schedule(
  cimunit_schedule_t *cs, 
  const char *sched_string, 
  cimunit_thread_amount_t numThreads)
{
  size_t i;
  cs->numThreads = numThreads;
  cs->sched_string = sched_string;

  cimunit_get_num_events(sched_string, &(cs->numEvents));

  //Replace this hardcode with actual parsing of the schedule.
  cs->events = 
    (cimunit_event_t**)malloc(sizeof(cimunit_event_t*)*(cs->numEvents));
  /*
  for(i = 0; i < cs->numEvents ;++i){
    cs->events[i] = (cimunit_event_t*)malloc(sizeof(cimunit_event_t));
    //Should probably do per-event initialization in here. including
    //assigning any dependent events.
  }
  */

  //STATIC ASSIGNMENT OF DEPENECIES THIS IS JUST FOR TESTING OUT MY SAMPLE
  //PROGRAM!!!!
  char *name1 = (char*)malloc(sizeof(char)*8);
  strcpy(name1, "t2begin");
  char *name2 = (char*)malloc(sizeof(char)*6);
  strcpy(name2, "t1end");
  cs->events[0] = cimunit_event_init(name1);
  cs->events[1] = cimunit_event_init(name2);
  cimunit_event_t** begin_deps = 
    (cimunit_event_t**)malloc(sizeof(cimunit_event_t*));
  
  cimunit_event_add_action(cs->events[0], cs->events[1]);
}

int cimunit_destroy_schedule(cimunit_schedule_t *cs){
  int i;
  for(i=0; i<cs->numEvents; ++i){
    cimunit_event_destroy(cs->events[i]);
    free(cs->events[i]->event_name);
    free(cs->events[i]);
  }
  free(cs->events);
}

