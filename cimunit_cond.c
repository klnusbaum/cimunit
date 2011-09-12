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

#include "cimunit_cond.h"

int cimunit_cond_init(
  cimunit_cond *cond, 
  const cimunit_cond_attr *restrict attr)
{
  return pthread_cond_init(
    &(cond->cond_impl), 
    attr==NULL ? NULL : &(attr->attr_impl)  
  );
}

int cimunit_cond_destroy(cimunit_cond *cond){
  return pthread_cond_destroy(&(cond.cond_impl));
}

int cimunit_cond_wait(
  cimunit_cond *restrict cond,
  cimunit_mutex *restrict mutex)
{
  return pthread_cond_wait(cond->cond_impl, mutex->mutex_impl);
}

int cimunit_cond_broadcast(cimunit_cond *cond){
  return pthread_cond_broadcast(cond->cond_impl);
}

