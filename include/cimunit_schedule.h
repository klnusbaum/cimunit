/**
 * Copyright 2011 Kurtis L. Nusbaum & Dale Frampton
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
#include <stdlib.h>

#include "cimunit_event.h"
#include "cimunit_event_list.h"

typedef size_t cimunit_thread_amount_t;


/// Structure use to define a CIMUnit schedule
typedef struct cimunit_schedule {
    /// List of events involved in the schedule
    cimunit_event_list_t *event_list;


  cimunit_thread_amount_t numThreads;
  const char *sched_string; 
  cimunit_event_t **events;
  size_t numEvents;
} cimunit_schedule_t;


/// Create a new schedule from the passed string
///
/// \param schedule_string - schedule to be met
/// \return newly created and configured schedule object
cimunit_schedule_t *cimunit_schedule_parse(char *schedule_string);


/// Create a new schedule object
///
/// \return new schedule object
cimunit_schedule_t *cimunit_schedule_init();

/// Destroy the schedule object and free memory
void cimunit_schedule_destroy(cimunit_schedule_t *schedule);




int cimunit_get_event_names(const char *sched_string, char **event_names);

int cimunit_init_schedule(
  cimunit_schedule_t *cs, 
  const char *sched_string, 
  cimunit_thread_amount_t numThreads);

int cimunit_destroy_schedule(cimunit_schedule_t *cs);

int cimunit_get_schedule_event(
  const char *event_name,
  const cimunit_schedule_t *schedule,
  cimunit_event_t **found_event);

#endif //CIMUNIT_SCHEDULE_H
