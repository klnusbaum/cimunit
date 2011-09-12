#ifdef CIMUNIT_SCHEDULE_H
#define CIMUNIT_SCHEDULE_H
#include "cimunit_mutex.h"



typedef CIMUNIT_THREAD_AMOUNT int;

typedef struct{
  const char *event_name;
  cimunit_mutex event_lock; 
} cimunit_event;

typedef struct{
  cimunit_event *event;
  cimunit_event_map *leftChild;
  cimunit_event_map *rightChild; 
} cimunit_event_map;

/** \brief Struct which represents a schedule to be used in a test.*/
typedef struct{
  CIMUNIT_THREAD_AMOUNT numThreads;
  const char *sched_string; 
  cimunit_event_map *event_map;
} cimunit_schedule;

int cimunit_init_schedule(
  cimunit_schedule *cs, 
  const char *sched_string, 
  CIMUNIT_THREAD_AMOUNT numThreads);

int cimunit_destroy_schedule(cimunit_schedule *cs);

#endif //CIMUNIT_SCHEDULE_H
