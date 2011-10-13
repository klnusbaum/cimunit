/**
 * \file cimunit_barrier.h
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

#ifndef CIMUNIT_BARRIER_H
#define CIMUNIT_BARRIER_H
 
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#if PLATFORM_Darwin
  /// Include the customizations for Darwin
  #include "cimunit_barrier_unix.h"
#elif PLATFORM_Linux
  /// Include the customizations for Linxu
  #include "cimunit_barrier_unix.h"
#else
  #error "No PLATFORM_{system name} macro defined!"
#endif


/// Create a new barrier.
///
/// Create a new barrier and initialize it in the locked state.
///
/// \return the created barrier.  This barrier must be freed by
///         calling \ca cimunit_barrier_destroy.
cimunit_barrier_t *cimunit_barrier_init();

/// Destroy a barrier
///
/// Destroys a previously created barrier.  The results are undefined
/// if the barrier was never initialized.
///
/// \param barrier - the barrier to be destroyed
void cimunit_barrier_destroy(cimunit_barrier_t *barrier);

/// Wait at the barrier until it is unlocked
///
/// Pause the task until the specified barrier is unlocked.
///
/// \param barrier - the barrier to wait at
void cimunit_barrier_wait(cimunit_barrier_t *barrier);

/// Unlock a barrier
///
/// Unlock the barrier and allow all tasks that are waiting at the barrier
/// to continue.  New tasks that wait at the barrier will be passed through
///
/// \param barrier - the barrier to be unlocked
void cimunit_barrier_unlock(cimunit_barrier_t *barrier);

/// Lock a barrier
///
/// Lock the barrier and prevent all the tasks currently waiting at the
/// barrier to pend.  New tasks that wait at the barrier will also pend.
///
/// \param barrier - the barrier to be locked
void cimunit_barrier_lock(cimunit_barrier_t *barrier);

#endif // CIMUNIT_BARRIER_H