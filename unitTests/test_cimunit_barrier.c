/**
 * \file test_cimunit_barrier.c
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
 
#include <stdio.h>
#include "testMain.h"

#include "cimunit_barrier.h"
#include "cimunit_thread.h"

cimunit_barrier_t my_barrier;

void *bwait(void *value) {
  int *intValue = value;
  cimunit_barrier_wait(&my_barrier);
  ++(*intValue);
}


// Under high-load conditions this test mail fail due to the timeouts.
// This failure is not indicative of a failure of the barrier, but of
// a deterministic method by which this unit test can verify that the
// threads have or have not passed the barrier.
static void barrier_test(void) {
  int value1 = 0;
  int value2 = 0;

  cimunit_thread_t thread1;
  cimunit_thread_t thread2;

  cimunit_barrier_init(&my_barrier);
  cimunit_thread_create(&thread1, bwait, &value1);
  cimunit_thread_create(&thread2, bwait, &value2);
    

  cimunit_thread_sleep(500);

  CU_ASSERT_FALSE(value1);
  CU_ASSERT_FALSE(value2);

  cimunit_barrier_unlock(&my_barrier);

  cimunit_thread_sleep(500);
  CU_ASSERT_TRUE(value1);
  CU_ASSERT_TRUE(value2);
    
  cimunit_thread_join(thread1, NULL);
  cimunit_thread_join(thread2, NULL);

  cimunit_barrier_destroy(&my_barrier);
}


static CU_TestInfo tests_cimunit[] = {
  {"barrier test",  barrier_test},
  CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  {"suite_cimunit_schedule", NULL, NULL, tests_cimunit},
  CU_SUITE_INFO_NULL,
};

RUN_TEST_SUITES(suites, test_cimunit_barrier)

