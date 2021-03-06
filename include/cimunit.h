/**
 * \file cimunit.h
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
#ifndef CIMUNIT_H
#define CIMUNIT_H

#include "cimunit_schedule.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Global CIMUnit variable used by the CIMUnit test macros.
extern struct cimunit_schedule *g_cimunit_default_schedule;

/// \addtogroup cimunit CIMUnit Module
/// @{

/// Create a CIMUnit schedule
///
/// This differs from cimunit_schedule_parse by using a global variable that
/// works with the other CIMUnit macros to simplify test development in an
/// environment where only one test will be run at a time.
/// \todo Add code to free the previous schedule, while ensuring that any
///       references to schedule items are not freed until properly released.
///       The destroy code that was here was removed as there was a race
///       condition that after firing an event in a low priority thread, the
///       higher priority thread controlling the testing began a new test
///       which defined a new schedule.  The fire actions from the previous
///       test hadn't been completed and accessed memory that was no longer
///       valid.
#define CIMUNIT_SCHEDULE(schedule) \
    g_cimunit_default_schedule = cimunit_schedule_parse(schedule)


/// Fire a CIMUnit event
///
/// This differs from cimunit_event_fire as it uses a global variable to
/// simplify test development.
#define CIMUNIT_FIRE(eventName) \
    cimunit_schedule_fire(g_cimunit_default_schedule, eventName)


/// Name a thread in the schedule
///
/// This macro gives a name to the currently executing thread
#define CIMUNIT_THREAD_NAME(threadName) \
    cimunit_schedule_set_thread_name(g_cimunit_default_schedule, \
                                     cimunit_thread_self(), \
                                     threadName)

/// @}

#ifdef __cplusplus
}
#endif

#endif //CIMUNIT_H
