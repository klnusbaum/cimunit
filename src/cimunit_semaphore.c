/**
 * \file cimunit_semaphore.c
 *
 * Copyright 2011 Dale Frampton
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

#include "cimunit_semaphore.h"


cimunit_semaphore_t *cimunit_semaphore_init(void);

void cimunit_semaphore_destroy(cimunit_semaphore_t *semaphore);

void cimunit_semaphore_signal(cimunit_semaphore_t *semaphore);

void cimunit_semaphore_wait(cimunit_semaphore_t *semaphore);

int cimunit_mutex_init(
  cimunit_mutex_t *mutex, 
  const cimunit_mutex_attr_t *attr)
{
  return pthread_mutex_init(mutex, attr);
}

int cimunit_mutex_destroy(cimunit_mutex_t *mutex){
  return pthread_mutex_destroy(mutex);
}

int cimunit_mutex_lock(cimunit_mutex_t *mutex){
  return pthread_mutex_lock(mutex);
}

int cimunit_mutex_unlock(cimunit_mutex_t *mutex){
  return pthread_mutex_unlock(mutex);
}
//TODO implement init functions for the attributes (May not be necessary for
//my purposed)

