/**
 * \file cimunit_thread.h
 *
 * Copyright 2011 Dale Frampton and Kurtis Nusbaum
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

#include <pthread.h>
#include <unistd.h>
#include "cimunit_thread.h"

int cimunit_thread_create(
  cimunit_thread_t * RESTRICT thread, 
  cimunit_task_entry_t function,
  void *RESTRICT arg)
{
  int result;

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  result = pthread_create(thread, &attr, function, arg);
  //pthread_attr_destory(&attr);

  return result;
}

int cimunit_thread_join(cimunit_thread_t thread, void **value_ptr){
  return pthread_join(thread, value_ptr);
}

cimunit_thread_t cimunit_thread_self(){
  return pthread_self();
}

void cimunit_thread_sleep(int time) {
    usleep(time);
}
