#ifndef CIM_MUTEX_H
#define CIM_MUTEX_H
#include <pthread.h>

typedef struct{
  pthread_mutex_t mutex_impl;
} cimunit_mutex;

typedef struct{
  pthread_muteattr_t attr_impl;
} cimunit_mutex_attr;

int cimunit_mutex_init(
  cimunit_mutex *mutex, 
  const cimunit_mutex_attr *attr);

int cimunit_mutex_destroy(cimunit_mutex *mutex);
int cimunit_mutex_lock(cimunit_mutex *mutex);
int cimunit_mutex_unlock(cimunit_mutex *mutex);

#endif

