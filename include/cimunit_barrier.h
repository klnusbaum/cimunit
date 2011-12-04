/**
 * \file cimunit_barrier.h
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

#ifndef CIMUNIT_BARRIER_H
#define CIMUNIT_BARRIER_H
 
#if defined(PLATFORM_Darwin) || \
    defined(PLATFORM_Linux)
  #include "cimunit_barrier_pthread.h"
#elif PLATFORM_VxWorks
  /// Include the customizations for VxWorks
  #include "cimunit_barrier_vxworks.h"
#else
  #error "No PLATFORM_{system name} macro defined!"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/// \addtogroup cimunit_barrier cimunit_barrier Module
/// @{
/// The cimunit_barrier object is the key component that allows CIMUnit to
/// operate.  It provides a mechanism where multiple threads can pend on a
/// single object and can be unblocked en masse.  A locked barrier causes all
/// threads that wait on it to be blocked while an unlocked barrier causes
/// all threads currently waiting on it to be unblocked and any new threads
/// that wait on it to not be blocked.
///

/// \brief Create a new barrier.
///
/// Create a new barrier and initialize it in the locked state.
///
/// \param barrier - Barrier to initialize.
/// \return 0 if the initialization was succesful, error code otherwise.
int cimunit_barrier_init(cimunit_barrier_t *barrier);

/// \brief Destroy a barrier
///
/// Destroys a previously created barrier.  The results are undefined
/// if the barrier was never initialized.
///
/// \param barrier - the barrier to be destroyed
/// \return 0 if successful, error code other wise
int cimunit_barrier_destroy(cimunit_barrier_t *barrier);

/// \brief Wait at the barrier until it is unlocked
///
/// Block the task until the specified barrier is unlocked.
///
/// \param barrier - the barrier to wait at
void cimunit_barrier_wait(cimunit_barrier_t *barrier);

/// \brief Unlock a barrier
///
/// Unlock the barrier and unblock all tasks that are blocked at the barrier.
/// New tasks that wait at the barrier will not be blocked.
///
/// \param barrier - the barrier to be unlocked
void cimunit_barrier_unlock(cimunit_barrier_t *barrier);

/// \brief Lock a barrier
///
/// Lock the barrier and cause all new tasks that wait at the barrier to
/// block.
///
/// \param barrier - the barrier to be locked
void cimunit_barrier_lock(cimunit_barrier_t *barrier);

/// @}

#ifdef __cplusplus
}
#endif

#endif // CIMUNIT_BARRIER_H
