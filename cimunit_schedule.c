#include "cimunit_schedule.h"

int getNumEvents(const char* string);
int getEventNames(char** events, const char *sched_string, int numEvents);

int cimunit_init_event_map(
  const char *sched_string, 
  cimunit_event_map *event_map)
{
  numEvents = getNumEvents(sched_string);
  char **events = (char**)malloc(sizeof(char*)*numEvents);
  getEventNames(events, const char *sched_string, numEvents);

}

int cimunit_init_schedule(
  cimunit_schedule *cs, 
  const char *sched_string, 
  CIMUNIT_THREAD_AMOUNT numThreads)
{
  cs->numThreads = numThreads;
  cs->sched_string = sched_string;
  cimunit_event_map *event_map=NULL;
  cimunit_init_event_map(sched_string, event_map);
}

int cimunit_destroy_schedule(cimunit_schedule *cs){

}

int getNumEvents(const char* string){
  numEvents =0;
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

