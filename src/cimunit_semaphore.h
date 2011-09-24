/**
 * \file cimunit_semaphore.h
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

#ifndef CIMUNIT_SEMAPHORE_H
#define CIMUNIT_SEMAPHORE_H

#include <pthread.h>

typedef sem_t cimunit_semaphore_t;


void cimunit_semaphore_destroy(cimunit_semaphore_t *semaphore);

void cimunit_semaphore_signal(cimunit_semaphore_t *semaphore);

void cimunit_semaphore_wait(cimunit_semaphore_t *semaphore);


#endif // CIMUNIT_SEMAPHORE_H

