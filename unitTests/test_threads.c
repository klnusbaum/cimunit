/*
 * \file test_cimunit_event.c
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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cimunit.h"
#include "testMain.h"

static void test_cimunit_thread_setname(void)
{
  const char set_name[] = "steve";
  #if PLATFORM_Darwin
  cimunit_thread_setname(set_name);
  #else
  cimunit_thread_setname(cimunit_thread_self(), set_name);
  #endif
  char retrieved_name[CIMUNIT_MAX_THREAD_NAME_LENGTH];
  cimunit_thread_getname(
    cimunit_thread_self(),
    retrieved_name,
    CIMUNIT_MAX_THREAD_NAME_LENGTH);
  CU_ASSERT_STRING_EQUAL(set_name, retrieved_name);
}

#if PLATFORM_Darwin
#else

cimunit_mutex_t stall_mutex;
static void *stalling_function(void *arg){
  cimunit_mutex_lock(&stall_mutex);
  cimunit_mutex_unlock(&stall_mutex);
}


static void test_cimunit_thread_set_other_name(void){
  cimunit_mutex_init(&stall_mutex, NULL);
  cimunit_mutex_lock(&stall_mutex);

  const char set_name[] = "steve";
  cimunit_thread_t other_thread;

  cimunit_thread_create(&other_thread, NULL, stalling_function, NULL);
  
  cimunit_thread_setname(other_thread, set_name);
  char retrieved_name[CIMUNIT_MAX_THREAD_NAME_LENGTH];
  cimunit_thread_getname(
    other_thread,
    retrieved_name,
    CIMUNIT_MAX_THREAD_NAME_LENGTH);
  CU_ASSERT_STRING_EQUAL(set_name, retrieved_name);
  printf("Real name \"%s\" ", set_name);
  printf("Retrieved name \"%s\" ", retrieved_name);
  cimunit_mutex_unlock(&stall_mutex);
  cimunit_thread_join(other_thread, NULL);
  cimunit_mutex_destroy(&stall_mutex);
}
#endif

static CU_TestInfo test_threads[] = {
  {"set name", test_cimunit_thread_setname },
  #if PLATFORM_Darwin
  #else
  {"set other name", test_cimunit_thread_set_other_name },
  #endif
  CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  {"suite_cimunit_threads", NULL, NULL, test_threads},
  CU_SUITE_INFO_NULL,
};

RUN_TEST_SUITES( suites )
