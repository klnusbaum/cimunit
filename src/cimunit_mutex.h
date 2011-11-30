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

#if defined(PLATFORM_Darwin) || \
    defined(PLATFORM_Linux)
  #include "cimunit_mutex_pthread.h"
#elif PLATFORM_VxWorks
  /// Include the customizations for Linux
  #include "cimunit_mutex_vxworks.h"
#else
  #error "No PLATFORM_{system name} macro defined!"
#endif

/// \addtogroup cimunit_mutex cimunit_mutex Module
/// @{

/// Create a new mutex
/// \param mutex - pointer to mutex object
/// \param attr - mutex attributes
int cimunit_mutex_init(
  cimunit_mutex_t *mutex, 
  const cimunit_mutex_attr_t *attr);


/// Destroy a mutex
/// \param mutex - mutex to destroy
int cimunit_mutex_destroy(cimunit_mutex_t *mutex);


/// Lock a mutex
///
/// This method blocks if the mutex is already locked
/// \param mutex - mutex to lock
int cimunit_mutex_lock(cimunit_mutex_t *mutex);


/// Unlock a mutex
/// \param mutex - mutex to unlock
int cimunit_mutex_unlock(cimunit_mutex_t *mutex);


/// Attempt to lock a mutex
///
/// This method doesn't blocks if the mutex is already locked
/// \param mutex - mutex to lock
/// \return 0 if the mutex was locked else non-zero
int cimunit_mutex_trylock(cimunit_mutex_t *mutex);

/// @}

#endif

