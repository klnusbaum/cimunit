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
  cimunit_thread_table_t thread_table;
  cimunit_thread_table_init(&thread_table);
  const char set_name[] = "steve";
  cimunit_set_thread_name(&thread_table, cimunit_thread_self(), set_name);
 
  char retrieved_name[CIMUNIT_MAX_THREAD_NAME_LENGTH];
  cimunit_get_thread_name(&thread_table, cimunit_thread_self(), retrieved_name);
  CU_ASSERT_STRING_EQUAL(set_name, retrieved_name);
  cimunit_thread_table_destroy(&thread_table);
}

static CU_TestInfo test_threads[] = {
  {"set name", test_cimunit_thread_setname },
  CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  {"suite_cimunit_threads", NULL, NULL, test_threads},
  CU_SUITE_INFO_NULL,
};

RUN_TEST_SUITES( suites )
