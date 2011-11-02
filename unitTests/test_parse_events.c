/*
 * \file test_parse_events.c
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
#include <assert.h>

#include "testMain.h"
#include "cimunit.h"

static void test_parse_event_single(void)
{
    cimunit_schedule_t *schedule = cimunit_schedule_parse("a->x");

    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));

    /// - Add event to the fired event list
    cimunit_event_t *event =
      cimunit_event_list_find(schedule->event_list, "a");
    cimunit_add_event_to_table(&schedule->fired_event_list, event, NULL);

    CU_ASSERT_TRUE(cimunit_schedule_parse_runtime(schedule, "x"));
}


static void test_parse_event_double(void)
{
    cimunit_schedule_t *schedule = cimunit_schedule_parse("a->x,b->a");

    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "a"));
    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));
    
    /// - Fire event b, should unblock event a
    cimunit_schedule_fire(schedule, "b");
    
    CU_ASSERT_TRUE(cimunit_schedule_parse_runtime(schedule, "a"));
    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));

    /// - Fire event a, should unlock event x
    cimunit_schedule_fire(schedule, "a");
    
    CU_ASSERT_TRUE(cimunit_schedule_parse_runtime(schedule, "a"));
    CU_ASSERT_TRUE(cimunit_schedule_parse_runtime(schedule, "x"));
}


static void test_parse_event_or(void)
{
    cimunit_schedule_t *schedule = cimunit_schedule_parse("a||b->x");

    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));
    
    /// - Fire event b, should unblock event a
    cimunit_schedule_fire(schedule, "b");
    
    CU_ASSERT_TRUE(cimunit_schedule_parse_runtime(schedule, "x"));
    
    /// - Rerun schedule, but test event a
    cimunit_schedule_destroy(schedule);
    schedule = cimunit_schedule_parse("a||b->x");

    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));
    
    /// - Fire event b, should unblock event a
    cimunit_schedule_fire(schedule, "a");
    
    CU_ASSERT_TRUE(cimunit_schedule_parse_runtime(schedule, "x"));
}


static void test_parse_event_and(void)
{
    cimunit_schedule_t *schedule = cimunit_schedule_parse("a&&b->x");

    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));
    
    /// - Fire event b, should unblock event a
    cimunit_schedule_fire(schedule, "b");
    
    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));
    
    /// - Rerun schedule, but test event a
    cimunit_schedule_destroy(schedule);
    schedule = cimunit_schedule_parse("a&&b->x");

    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));
    
    /// - Fire event b, should unblock event a
    cimunit_schedule_fire(schedule, "a");
    
    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));

    /// - Fire event b, should unblock event a
    cimunit_schedule_fire(schedule, "b");

    CU_ASSERT_TRUE(cimunit_schedule_parse_runtime(schedule, "x"));    
}


static void test_parse_event_order(void)
{
    cimunit_schedule_t *schedule = cimunit_schedule_parse("a||b&&c->x");

    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));
    
    cimunit_schedule_fire(schedule, "a");
    
    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));

    cimunit_schedule_fire(schedule, "c");

    CU_ASSERT_TRUE(cimunit_schedule_parse_runtime(schedule, "x"));
    
    /// - Rerun schedule, but test event a
    cimunit_schedule_destroy(schedule);
    schedule = cimunit_schedule_parse("a||b&&c->x");

    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));

    cimunit_schedule_fire(schedule, "b");
    
    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));

    cimunit_schedule_fire(schedule, "c");

    CU_ASSERT_TRUE(cimunit_schedule_parse_runtime(schedule, "x"));
}


static void test_parse_event_paren(void)
{
    cimunit_schedule_t *schedule = cimunit_schedule_parse("a||(b&&c)->x");

    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));
    
    cimunit_schedule_fire(schedule, "a");
    
    CU_ASSERT_TRUE(cimunit_schedule_parse_runtime(schedule, "x"));
    
    /// - Rerun schedule, but test event a
    cimunit_schedule_destroy(schedule);
    schedule = cimunit_schedule_parse("a||(b&&c)->x");

    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));

    cimunit_schedule_fire(schedule, "b");
    
    CU_ASSERT_FALSE(cimunit_schedule_parse_runtime(schedule, "x"));

    cimunit_schedule_fire(schedule, "c");

    CU_ASSERT_TRUE(cimunit_schedule_parse_runtime(schedule, "x"));
}


static CU_TestInfo tests_parse_event_single[] = {
  {"parse_single", test_parse_event_single},
  {"parse_double", test_parse_event_double},
  {"parse_or", test_parse_event_or},
  {"parse_and", test_parse_event_and},
  {"parse_order", test_parse_event_order},
  CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  {"suite_parse_event_single", NULL, NULL, tests_parse_event_single},
  CU_SUITE_INFO_NULL,
};

void AddParseEventTests(void)
{
  cimunit_register_test_suites(suites);
}

RUN_TEST_SUITE(AddParseEventTests())
