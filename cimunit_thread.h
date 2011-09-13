/**
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
#ifndef CIMUNIT_THREAD_H
#define CIMUNIT_THREAD_H

#include <pthread.h>
typedef cimunit_thread pthread_t;
typedef cimunit_thread_attr pthread_attr_t;
int cimunit_thread_create(
  cimunit_thread *restrict thread, 
  const cimunit_thread_attr *restrict attr,
  void *(*function)(void *),
  void *restrict arg);

int cimunit_join(cimunit_thread, void **value_ptr);
#endif //CIMUNIT_THREAD_H
