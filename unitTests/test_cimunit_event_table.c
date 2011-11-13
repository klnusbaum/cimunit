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

#include "testMain.h"
#include "cimunit_event_table.h"

#define BASIC_EVENT_TABLE_INIT \
  cimunit_event_table_t event_table; \
  cimunit_event_table_init(&event_table, NULL);

#define BASIC_EVENT_TABLE_DESTROY \
  cimunit_event_table_destroy(&event_table);


static void test_cimunit_event_table_destroy(void){
  BASIC_EVENT_TABLE_INIT

  CU_ASSERT_PTR_NULL(event_table.head); 
  CU_ASSERT_PTR_NULL(event_table.tail); 
  //CU_ASSERT_EQUAL(0,cimunit_mutex_trylock(&(event_table.lock)));
  cimunit_mutex_unlock(&(event_table.lock));

  BASIC_EVENT_TABLE_DESTROY
}

static void test_cimunit_event_table_add(void){
  cimunit_event_t event;
  char event_name[] = "eventa";
  cimunit_event_table_entry_t *added_entry;
  cimunit_event_table_entry_t *found_entry;

  BASIC_EVENT_TABLE_INIT

  cimunit_event_init(&event, event_name);


  cimunit_add_event_to_table(&event_table, &event, &added_entry);
  cimunit_find_event_in_table(&event_table, event_name, &found_entry);
  CU_ASSERT_PTR_NOT_NULL(found_entry);
  CU_ASSERT_PTR_EQUAL(found_entry, added_entry);

  BASIC_EVENT_TABLE_DESTROY
}

static CU_TestInfo tests_cimunit_event_table[] = {
  {"init", test_cimunit_event_table_destroy},
  CU_TEST_INFO_NULL,
};

static CU_SuiteInfo suites[] = {
  {"suite_cimunit_event_table", NULL, NULL, tests_cimunit_event_table}, 
  CU_SUITE_INFO_NULL,
};

RUN_TEST_SUITES(suites, test_cimunit_event_table);
