/**
 * \file cimunit_mutex.h
 *
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

#ifndef CIMUNIT_MUTEX_H
#define CIMUNIT_MUTEX_H
#include <pthread.h>

typedef pthread_mutex_t cimunit_mutex_t;
typedef pthread_mutexattr_t cimunit_mutex_attr_t;

int cimunit_mutex_init(
  cimunit_mutex_t *mutex, 
  const cimunit_mutex_attr_t *attr);

int cimunit_mutex_destroy(cimunit_mutex_t *mutex);
int cimunit_mutex_lock(cimunit_mutex_t *mutex);
int cimunit_mutex_unlock(cimunit_mutex_t *mutex);

#endif

