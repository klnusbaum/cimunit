#include "cimunit_mutex.h"

int cimunit_mutex_init(
  cimunit_mutex *mutex, 
  const cimunit_mutex_attr *attr)
{
  return pthread_mutex_init(
    &(mutex->mutex_impl), 
    attr==NULL ? NULL : &(attr->attr_impl)  
  );
}

int cimunit_mutex_destroy(cimunit_mutex *mutex){
  return pthread_mutex_destroy(&(mutex.mutex_impl));
}

int cimunit_mutex_lock(cimunit_mutex *mutex){
  return pthread_mutex_lock(&(mutex->mutex_impl));
}

int cimunit_mutex_unlock(cimunit_mutex *mutex){
  return pthread_mutex_unlock(&(mutex->mutex_impl));
}
//TODO implement init functions for the attributes (May not be necessary for
//my purposed)

