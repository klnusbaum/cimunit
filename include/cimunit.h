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
#ifndef CIMUNIT_H
#define CIMUNIT_H

#include "cimunit_schedule.h"


/// Fire a CIMUnit event
///
/// \param schedule - schedule used to control event ordering
/// \param event - name of the event to be fired
/// \return true if the event was found, else false
bool cimunit_fire(struct cimunit_schedule *schedule, char *eventName);


/// Global CIMUnit variable used by the CIMUnit test macros.
extern struct cimunit_schedule *g_cimunit_default_schedule;


/// Create a CIMUnit schedule
///
/// This differs from cimunit_schedule_parse by using a global variable that works
/// with the other CIMUnit macros to simplify test development in an environment where
/// only one test will be run at a time.
#define CIMUNIT_SCHEDULE(schedule) \
    if (g_cimunit_default_schedule) { \
        cimunit_schedule_destroy(g_cimunit_default_schedule); \
    } \
    g_cimunit_default_schedule = cimunit_schedule_parse(schedule)


/// Fire a CIMUnit event
///
/// This differs from cimunit_event_fire as it uses a global variable to simplify test
/// development.
#define CIMUNIT_FIRE(eventName) \
    cimunit_fire(g_cimunit_default_schedule, eventName) \


#include "cimunit_tester.h"

/** \name Cimunit Typedefs */
//@{

/** \brief Type indicating an amount of threads */

typedef size_t cimunit_thread_id_t;

typedef struct{
  cimunit_schedule_t *schedule;
  cimunit_thread_id_t thread;
} cimunit_test_args_t;

struct cimunit_schedule;

//@}

/** \name Cimunit Functions */
//@{

int cimunit_run_tests(cimunit_tester_t *tester);

//@}

/** \name Cimunit Helper Macros */
//@{

#define CIMUNIT_TEST(TEST_GROUP, TEST_NAME) \
 void* TEST_GROUP##_##TEST_NAME##_Cimunit_Test(void *args) 

#define CIMUNIT_FIRE_EVENT(EVENT) \
  cimunit_event_t *EVENT; \
  cimunit_get_schedule_event(  \
    #EVENT ,  \
    ((cimunit_test_args_t*)args)->schedule,  \
    &EVENT );\
  if( EVENT != NULL){ \
    cimunit_event_fire( EVENT ); \
  }



#define CIMUNIT_ADD_TEST_SCHEDULE(TESTER, TEST_GROUP, TEST_NAME, SCHEDULE) \
  cimunit_add_test(&TESTER, TEST_GROUP##_##TEST_NAME##_Cimunit_Test, &SCHEDULE);

#define CIMUNIT_TNUMBER \
  ((cimunit_test_args_t*)args)->thread
//@}

#endif //CIMUNIT_H
