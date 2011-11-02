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

#include "cimunit_thread.h"
int cimunit_thread_create(
  cimunit_thread_t * RESTRICT thread, 
  const cimunit_thread_attr_t *RESTRICT attr,
  void *(*function)(void *),
  void *RESTRICT arg)
{
  return pthread_create(thread, attr, function, arg);
}

int cimunit_thread_join(cimunit_thread_t thread, void **value_ptr){
  return pthread_join(thread, value_ptr);
}

#if PLATFORM_Darwin
int cimunit_thread_setname(const char *name){
    return pthread_setname_np(name);
}
#else
int cimunit_thread_setname(cimunit_thread_t thread, const char *name){
    return pthread_setname_np(thread, name);
}
#endif

int cimunit_thread_getname(cimunit_thread_t thread, char *name, size_t buf_size)
{
    //TODO throw error if buf_size is greater 
    // than CIMUNIT_MAX_THREAD_NAME_LENGTH
    return pthread_getname_np(thread, name, buf_size);
}

cimunit_thread_t cimunit_thread_self(){
  return pthread_self();
}

