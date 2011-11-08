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
#ifndef CIMUNIT_THREAD_H
#define CIMUNIT_THREAD_H

#include "cimunit_platform.h"

int cimunit_thread_create(
  cimunit_thread_t *RESTRICT thread, 
  const cimunit_thread_attr_t * RESTRICT  attr,
  void *(*function)(void *),
  void * RESTRICT arg);

int cimunit_thread_join(cimunit_thread_t thread, void **value_ptr);

cimunit_thread_t cimunit_thread_self();

#endif //CIMUNIT_THREAD_H
