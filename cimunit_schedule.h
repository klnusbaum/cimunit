/**
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

#ifdef CIMUNIT_SCHEDULE_H
#define CIMUNIT_SCHEDULE_H
#include "cimunit_mutex.h"



typedef CIMUNIT_THREAD_AMOUNT int;

typedef struct{
  const char *event_name;
  cimunit_mutex event_lock; 
} cimunit_event;

typedef struct{
  cimunit_event *event;
  cimunit_event_map *leftChild;
  cimunit_event_map *rightChild; 
} cimunit_event_map;

/** \brief Struct which represents a schedule to be used in a test.*/
typedef struct{
  CIMUNIT_THREAD_AMOUNT numThreads;
  const char *sched_string; 
  cimunit_event_map *event_map;
} cimunit_schedule;

int cimunit_init_schedule(
  cimunit_schedule *cs, 
  const char *sched_string, 
  CIMUNIT_THREAD_AMOUNT numThreads);

int cimunit_destroy_schedule(cimunit_schedule *cs);

#endif //CIMUNIT_SCHEDULE_H
