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
#ifndef CIMUNIT_SCHEDULE_H
#define CIMUNIT_SCHEDULE_H

typedef CIMUNIT_THREAD_AMOUNT int;


/** \brief Struct which represents a schedule to be used in a test.*/
typedef struct{
  CIMUNIT_THREAD_AMOUNT numThreads;
  const char *sched_string; 
  cimunit_event **events;
  size_t numEvents;
} cimunit_schedule;

int cimunit_init_schedule(
  cimunit_schedule *cs, 
  const char *sched_string, 
  CIMUNIT_THREAD_AMOUNT numThreads);

int cimunit_destroy_schedule(cimunit_schedule *cs);

int cimunit_get_schedule_event(
  const char *event_name,
  cimunit_schedule *schedule,
  cimunit_event *found_event);

#endif //CIMUNIT_SCHEDULE_H
