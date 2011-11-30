/**
 * \file cimunit_mutex_vxworks.c
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

#include "cimunit_mutex.h"

int cimunit_mutex_init(
  cimunit_mutex_t *mutex, 
  const cimunit_mutex_attr_t *attr)
{
  *mutex = semMCreate(0);
}

int cimunit_mutex_destroy(cimunit_mutex_t *mutex){
  return semDelete(*mutex);
}

int cimunit_mutex_lock(cimunit_mutex_t *mutex){
  return semTake(*mutex, WAIT_FOREVER);
}

int cimunit_mutex_unlock(cimunit_mutex_t *mutex){
  return semGive(*mutex);
}

