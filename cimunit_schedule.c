#include "cimunit_schedule.h"

int cimunit_init_schedule(
  cimunit_schedule *cs, 
  const char *sched_string, 
  CIMUNIT_THREAD_AMOUNT numThreads)
{
  cs->numThreads = numThreads;
  cs->sched_string = sched_string;
}

int cimunit_destroy_schedule(cimunit_schedule *cs){

}

int getNumEvents(const char* string, int &numEvents){
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

