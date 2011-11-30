/**
 * \file cimunit_barrier_vxworks.c
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
 
#include "cimunit_barrier.h"

#include <stdlib.h>


int cimunit_barrier_init(cimunit_barrier_t *barrier)
{
    cimunit_mutex_init(&barrier->mutex, NULL);

    // Create a counting semaphore with an initial value of 0.
    barrier->cond = semCCreate(0, 0);

    barrier->is_locked = TRUE;
    return 0;
}


int cimunit_barrier_destroy(cimunit_barrier_t *barrier)
{
    semDelete(barrier->cond);
    cimunit_mutex_destroy(&barrier->mutex);
    /// \todo actually return an error code is somethign goes wrong
   return 0;
}


void cimunit_barrier_wait(cimunit_barrier_t *barrier)
{
    semTake(barrier->cond, WAIT_FOREVER);
    cimunit_mutex_lock(&barrier->mutex);
    if (!barrier->is_locked)
    {
        // Let the next thread in line pass the barrier
        semGive(barrier->cond);
    }
    cimunit_mutex_unlock(&barrier->mutex);
}


void cimunit_barrier_unlock(cimunit_barrier_t *barrier)
{
    cimunit_mutex_lock(&barrier->mutex);
    if (barrier->is_locked)
    {
        barrier->is_locked = FALSE;
        semGive(barrier->cond);
    }
    cimunit_mutex_unlock(&barrier->mutex);
}


void cimunit_barrier_lock(cimunit_barrier_t *barrier)
{
    cimunit_mutex_lock(&barrier->mutex);
    barrier->is_locked = TRUE;
    cimunit_mutex_unlock(&barrier->mutex);                    
}

