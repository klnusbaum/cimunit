/**
 * \file cimunit_thread_pthread.h
 *
 * Copyright 2011 Dale Frampton & Kurtis L. Nusbaum
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
#ifndef CIMUNIT_THREAD_PTHREAD_H
#define CIMUNIT_THREAD_PTHREAD_H

#include "pthread.h"

#ifdef __cplusplus
extern "C" {
#endif
  
/// \addtogroup cimunit_thread cimunit_thread Module
/// @{

/// Pthread implementation of a thread ID.
typedef pthread_t cimunit_thread_t;

/// @}

#ifdef __cplusplus
}
#endif
  
#endif // CIMUNIT_THREAD_PTHREAD_H
