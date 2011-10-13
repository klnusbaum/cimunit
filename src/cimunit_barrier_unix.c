/**
 * \file cimunit_barrier_unix.c
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
 
#include <stdlib.h>

#include "cimunit_barrier.h"


cimunit_barrier_t *cimunit_barrier_init()
{
    cimunit_barrier_t *barrier = malloc(sizeof(cimunit_barrier_t));
    pthread_mutex_init(&barrier->mutex, NULL);
    pthread_cond_init(&barrier->cond, NULL);
    barrier->is_locked = true;
}


void cimunit_barrier_destroy(cimunit_barrier_t *barrier)
{
    pthread_cond_destroy(&barrier->cond);
    pthread_mutex_destroy(&barrier->mutex);
    free(barrier);
}


void cimunit_barrier_wait(cimunit_barrier_t *barrier)
{
    pthread_mutex_lock(&barrier->mutex);
    if (barrier->is_locked)
    {
        pthread_cond_wait(&barrier->cond, &barrier->mutex);
        if (!barrier->is_locked)
        {
            // Let the next thread in line pass the barrier
            pthread_cond_signal(&barrier->cond);
        }
    }
    pthread_mutex_unlock(&barrier->mutex);
}


void cimunit_barrier_unlock(cimunit_barrier_t *barrier)
{
    pthread_mutex_lock(&barrier->mutex);
    barrier->is_locked = false;
    pthread_cond_signal(&barrier->cond);
    pthread_mutex_unlock(&barrier->mutex);                    
}


void cimunit_barrier_lock(cimunit_barrier_t *barrier)
{
    pthread_mutex_lock(&barrier->mutex);
    barrier->is_locked = true;
    pthread_mutex_unlock(&barrier->mutex);                    
}
