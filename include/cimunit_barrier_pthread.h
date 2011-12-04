/**
 * \file cimunit_barrier_pthread.h
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

#ifndef CIMUNIT_BARRIER_PTHREAD_H
#define CIMUNIT_BARRIER_PTHREAD_H

#include <pthread.h>

#include "cimunit_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/// \addtogroup cimunit_barrier cimunit_barrier Module
/// @{

/// \brief Pthreads barrier structure
///
/// The pthreads implementation of the barrier uses a condition variable.
/// When a thread waits on the barrier, the is_locked attribute is checked to
/// determine if the barrier is locked or unlocked.  If it's locked it waits
/// on cond and is blocked.  When the barrier is unlocked, cond is signaled
/// and one of the waiting threads unblocks.  That thread then signals cond
/// again which wakes another thread.  This continues until all threads that
/// were blocked on cond have been unblocked.
typedef struct cimunit_barrier_pthread {
    /// Mutex used to support the mutex/condition construct
    pthread_mutex_t mutex;
    /// Pthread condition used to support the mutex/condition construct
    pthread_cond_t cond;
    /// Is the barrier locked.  True if locked, else false.
    BOOL is_locked;
} cimunit_barrier_t;

/// @}

#ifdef __cplusplus
}
#endif
  
#endif // CIMUNIT_BARRIER_PTHREAD_H
