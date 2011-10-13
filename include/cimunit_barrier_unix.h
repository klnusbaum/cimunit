/**
 * \file cimunit_barrier_unix.h
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

#ifndef CIMUNIT_BARRIER_UNIX_H
#define CIMUNIT_BARRIER_UNIX_H


/// Structure containing the data needed to support the barrier.
typedef struct cimunit_barrier {
    /// Mutex used to support the mutex/condition construct
    pthread_mutex_t mutex;
    /// Pthread condition used to support the mutex/condition construct
    pthread_cond_t cond;
    /// Is the barrier locked.  True if locked, else false.
    bool is_locked;
} cimunit_barrier_t;

#endif // CIMUNIT_BARRIER_UNIX_H
