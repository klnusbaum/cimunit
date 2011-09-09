#ifdef CIMUNIT_SCHEDULE_H
#define CIMUNIT_SCHEDULE_H

typedef CIMUNIT_THREAD_AMOUNT int;

/** \brief Struct which represents a schedule to be used in a test.*/
typedef struct{
  CIMUNIT_THREAD_AMOUNT numThreads;
  const char *sched_string; 
} cimunit_schedule;

int cimunit_init_schedule(
  cimunit_schedule *cs, 
  const char *sched_string, 
  CIMUNIT_THREAD_AMOUNT numThreads);

int cimunit_destroy_schedule(cimunit_schedule *cs);

#endif //CIMUNIT_SCHEDULE_H
