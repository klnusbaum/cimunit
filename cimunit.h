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
#include "cimunit_tester.h"

/** \name Cimunit Typedefs */
//@{

/** \brief Type indicating an amount of threads */

typedef CIMUNIT_THREAD size_t;

typedef struct{
  cimunit_schedule *schedule;
  CIMUNIT_THREAD thread;
} cimunit_test_args;

//@}

/** \name Cimunit Functions */
//@{

int cimunit_run_tests(cimunit_tester *tester);

//@}

/** \name Cimunit Helper Macros */
//@{

#define CIMUNIT_TEST(TEST_GROUP, TEST_NAME) \
##TEST_GROUP##_##TEST_NAME##_Cimunit_Test( \
  void *args) 

#define CIMUNIT_FIRE_EVENT(EVENT) \
  cimunit_event EVENT; \
  cimunit_get_schedule_event(((*cimunit_test_args)args)->schedule,##EVENT##); \
  cimunit_fire_event(&EVENT);



#define CIMUNIT_ADD_TEST_SCHEDULE(TESTER, TEST_GROUP, TEST_NAME, SCHEDULE) \
  cimunit_add_test(&TESTER,##TEST_GROUP##_##TEST_NAME##_Cimunit_Test, SCHEDULE);

#define CIMUNIT_TNUMBER \
  ((cimunit_test_args*)args)->thread
//@}

#endif //CIMUNIT_H
