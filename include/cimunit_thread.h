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
#include "cimunit_thread.h"

#ifdef __cplusplus
extern "C" {
#endif
  
#if defined(PLATFORM_Darwin) || \
    defined(PLATFORM_Linux)
  #include "cimunit_thread_pthread.h"
#elif PLATFORM_VxWorks
  #include "cimunit_thread_vxworks.h"
#else
  #error "No PLATFORM_{system name} macro defined!"
#endif

/// \addtogroup cimunit_thread cimunit_thread Module
/// @{

/// Prototype for a thread entry point
typedef void *(*cimunit_task_entry_t)(void *);

/// Create a new thread
/// \param thread - thread identifier of newly created thread
/// \param function - thread entry point
/// \param arg - argument to the thread
int cimunit_thread_create(
  cimunit_thread_t *RESTRICT thread, 
  cimunit_task_entry_t function,
  void *RESTRICT arg);

/// Wait until the specified thread completes execution
/// \param thread - thread to wait for
/// \param value_ptr - location to store the return value
int cimunit_thread_join(cimunit_thread_t thread, void **value_ptr);

/// Return the thread identifier of the currently running thread
/// \return thread identifier
cimunit_thread_t cimunit_thread_self();

/// Put a thread to sleep for a fixed period of time
/// \param time - sleep time in milliseconds
void cimunit_thread_sleep(int time);

/// @}

#ifdef __cplusplus
}
#endif

#endif // CIMUNIT_THREAD_H
