/*
 * \file test_cimunit.c
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
#include <stdlib.h>
#include <string.h>

#include "cimunit.h"
#include "cimunit_schedule.h"
#include "cimunit_thread.h"
#include "testMain.h"


struct test_event_args {
    cimunit_schedule_t *schedule;
    int *value;
};

static void *test_eventA(void *ptr) {
    struct test_event_args *args = ptr;
    cimunit_schedule_fire(args->schedule, "a");
    *args->value *= 2;
}

static void *test_eventB(void *ptr) {
    struct test_event_args *args = ptr;
    cimunit_schedule_fire(args->schedule, "b");
    *args->value += 3;
}


static void test_cimunit_basic1(void)
{
    cimunit_thread_t threadA;
    cimunit_thread_t threadB;

    // Create schedule
    cimunit_schedule_t *schedule = cimunit_schedule_parse("a->b");
    int value = 1;

    // Pass data to threads
    struct test_event_args args;
    args.schedule = schedule;
    args.value = &value;
    
    // Create and execute threads
    cimunit_thread_create(&threadA, test_eventA, (void *)&args);
    cimunit_thread_create(&threadB, test_eventB, (void *)&args);

    cimunit_thread_join(threadA, NULL);
    cimunit_thread_join(threadB, NULL);

    // Verify SUT
    CU_ASSERT_EQUAL(value, 5);

    // Cleanup schedule
    cimunit_schedule_destroy(schedule);
}


static void test_cimunit_basic2(void)
{
    cimunit_thread_t threadA;
    cimunit_thread_t threadB;
    
    // Create schedule
    cimunit_schedule_t *schedule = cimunit_schedule_parse("b->a");
    int value = 1;

    // Pass data to threads
    struct test_event_args args;
    args.schedule = schedule;
    args.value = &value;
    
    // Create and execute threads
    cimunit_thread_create(&threadA, test_eventA, (void *)&args);
    cimunit_thread_create(&threadB, test_eventB, (void *)&args);

    cimunit_thread_join(threadA, NULL);
    cimunit_thread_join(threadB, NULL);

    // Verify SUT
    CU_ASSERT_EQUAL(value, 8);

    // Cleanup schedule
    cimunit_schedule_destroy(schedule);
}


static void *test_macro_eventA(void *ptr) {
    int *value = ptr;
    CIMUNIT_FIRE("a1");
    *value *= 2;
    CIMUNIT_FIRE("a2");
}

static void *test_macro_eventB(void *ptr) {
    int *value = ptr;
    CIMUNIT_FIRE("b1");
    *value += 3;
    CIMUNIT_FIRE("b2");
}

static void *test_macro_eventC(void *ptr) {
    int *value = ptr;
    CIMUNIT_FIRE("c1");
    *value *= 4;
    CIMUNIT_FIRE("c2");
}


static void test_cimunit_macro_basic1(void)
{
    cimunit_thread_t threadA;
    cimunit_thread_t threadB;
    int value = 1;
    
    // Create schedule
    CIMUNIT_SCHEDULE("a2->b1");

    // Create and execute threads
    cimunit_thread_create(&threadA, test_macro_eventA, (void *)&value);
    cimunit_thread_create(&threadB, test_macro_eventB, (void *)&value);

    cimunit_thread_join(threadA, NULL);
    cimunit_thread_join(threadB, NULL);

    // Verify SUT
    CU_ASSERT_EQUAL(value, 5);
}


static void test_cimunit_macro_basic2(void)
{
    cimunit_thread_t threadA;
    cimunit_thread_t threadB;
    int value = 1;
    
    // Create schedule
    CIMUNIT_SCHEDULE("b2->a1");

    // Create and execute threads
    cimunit_thread_create(&threadA, test_macro_eventA, (void *)&value);
    cimunit_thread_create(&threadB, test_macro_eventB, (void *)&value);

    cimunit_thread_join(threadA, NULL);
    cimunit_thread_join(threadB, NULL);
    
    // Verify SUT
    CU_ASSERT_EQUAL(value, 8);
}


static void test_cimunit_macro_two_actions1(void)
{
    cimunit_thread_t threadA;
    cimunit_thread_t threadB;
    cimunit_thread_t threadC;
    int value = 1;

    // Create schedule
    CIMUNIT_SCHEDULE("a2->b1,b2->c1");

    // Create and execute threads
    cimunit_thread_create(&threadA, test_macro_eventA, (void *)&value);
    cimunit_thread_create(&threadB, test_macro_eventB, (void *)&value);
    cimunit_thread_create(&threadC, test_macro_eventC, (void *)&value);

    cimunit_thread_join(threadA, NULL);
    cimunit_thread_join(threadB, NULL);
    cimunit_thread_join(threadC, NULL);

    // Verify SUT
    CU_ASSERT_EQUAL(value, 20);
}



static void test_cimunit_macro_two_actions1a(void)
{
    cimunit_thread_t threadA;
    cimunit_thread_t threadB;
    cimunit_thread_t threadC;
    int value = 1;
    
    // Create schedule
    CIMUNIT_SCHEDULE("b2->c1,a2->b1");

    // Create and execute threads
    cimunit_thread_create(&threadA, test_macro_eventA, (void *)&value);
    cimunit_thread_create(&threadB, test_macro_eventB, (void *)&value);
    cimunit_thread_create(&threadC, test_macro_eventC, (void *)&value);

    cimunit_thread_join(threadA, NULL);
    cimunit_thread_join(threadB, NULL);
    cimunit_thread_join(threadC, NULL);

    // Verify SUT
    CU_ASSERT_EQUAL(value, 20);
}


static void test_cimunit_macro_two_actions2(void)
{
    cimunit_thread_t threadA;
    cimunit_thread_t threadB;
    cimunit_thread_t threadC;
    int value = 1;
    
    // Create schedule
    CIMUNIT_SCHEDULE("c2->b1,b2->a1");

    // Create and execute threads
    cimunit_thread_create(&threadA, test_macro_eventA, (void *)&value);
    cimunit_thread_create(&threadB, test_macro_eventB, (void *)&value);
    cimunit_thread_create(&threadC, test_macro_eventC, (void *)&value);

    cimunit_thread_join(threadA, NULL);
    cimunit_thread_join(threadB, NULL);
    cimunit_thread_join(threadC, NULL);

    // Verify SUT
    CU_ASSERT_EQUAL(value, 14);
}


static void test_cimunit_macro_two_actions2a(void)
{
    cimunit_thread_t threadA;
    cimunit_thread_t threadB;
    cimunit_thread_t threadC;
    int value = 1;
    
    // Create schedule
    CIMUNIT_SCHEDULE("b2->a1,c2->b1");

    // Create and execute threads
    cimunit_thread_create(&threadA, test_macro_eventA, (void *)&value);
    cimunit_thread_create(&threadB, test_macro_eventB, (void *)&value);
    cimunit_thread_create(&threadC, test_macro_eventC, (void *)&value);

    cimunit_thread_join(threadA, NULL);
    cimunit_thread_join(threadB, NULL);
    cimunit_thread_join(threadC, NULL);

    // Verify SUT
    CU_ASSERT_EQUAL(value, 14);
}


static void test_cimunit_macro_or_conditional1(void)
{
    cimunit_thread_t threadB;
    cimunit_thread_t threadC;
    int value = 1;
    
    // Create schedule
    CIMUNIT_SCHEDULE("b2||a2->c1");

    // Create and execute threads
    cimunit_thread_create(&threadC, test_macro_eventC, (void *)&value);
    cimunit_thread_create(&threadB, test_macro_eventB, (void *)&value);

    cimunit_thread_join(threadB, NULL);
    cimunit_thread_join(threadC, NULL);

    // Verify SUT
    CU_ASSERT_EQUAL(value, 16);
}


static void test_cimunit_macro_or_conditional2(void)
{
    cimunit_thread_t threadA;
    cimunit_thread_t threadB;
    int value = 1;
    
    // Create schedule
    CIMUNIT_SCHEDULE("a2||c2->b1");

    // Create and execute threads
    cimunit_thread_create(&threadA, test_macro_eventA, (void *)&value);
    cimunit_thread_create(&threadB, test_macro_eventB, (void *)&value);

    cimunit_thread_join(threadA, NULL);
    cimunit_thread_join(threadB, NULL);

    // Verify SUT
    CU_ASSERT_EQUAL(value, 5);
}


static void test_cimunit_macro_and_conditional1(void)
{
     cimunit_thread_t threadA;
     cimunit_thread_t threadB;
     cimunit_thread_t threadC;
     int value = 1;
     int a;
        
    // Run tests multiple times attempting to simulate different schedules
    for (a = 0; a < 100; ++a) {
        // Create schedule
        CIMUNIT_SCHEDULE("b2&&a2->c1,a2->b1");
        value = 1;
    
        // Create and execute threads
        cimunit_thread_create(&threadC, test_macro_eventC, (void *)&value);
        cimunit_thread_create(&threadB, test_macro_eventB, (void *)&value);
        cimunit_thread_create(&threadA, test_macro_eventA, (void *)&value);
    
        cimunit_thread_join(threadA, NULL);
        cimunit_thread_join(threadB, NULL);
        cimunit_thread_join(threadC, NULL);
    
        // Verify SUT
        CU_ASSERT_EQUAL(value, 20);
    }
}


static void test_cimunit_macro_and_conditional2(void)
{
    cimunit_thread_t threadA;
    cimunit_thread_t threadB;
    cimunit_thread_t threadC;
    int value = 1;
    int a;
        
    // Run tests multiple times attempting to simulate different schedules
    for (a = 0; a < 100; ++a) {
        // Create schedule
        CIMUNIT_SCHEDULE("b2&&a2->c1,b2->a1");
        value = 1;
    
        // Create and execute threads
        cimunit_thread_create(&threadC, test_macro_eventC, (void *)&value);
        cimunit_thread_create(&threadB, test_macro_eventB, (void *)&value);
        cimunit_thread_create(&threadA, test_macro_eventA, (void *)&value);
    
        cimunit_thread_join(threadA, NULL);
        cimunit_thread_join(threadB, NULL);
        cimunit_thread_join(threadC, NULL);
    
        // Verify SUT
        CU_ASSERT_EQUAL(value, 32);
    }
}


static void *test_macro_eventA_threadX(void *ptr) {
    int *value = ptr;

    CIMUNIT_THREAD_NAME("x");
    CIMUNIT_FIRE("a1");
    *value *= 2;
    CIMUNIT_FIRE("a2");
}

static void *test_macro_eventA_threadZ(void *ptr) {
    int *value = ptr;

    CIMUNIT_THREAD_NAME("z");
    CIMUNIT_FIRE("a1");
    *value *= 2;
    CIMUNIT_FIRE("a2");
}


static void *test_macro_eventB_threadY(void *ptr) {
    int *value = ptr;

    CIMUNIT_THREAD_NAME("y");
    CIMUNIT_FIRE("b1");
    *value += 3;
    CIMUNIT_FIRE("b2");
}

static void *test_macro_eventC_threadZ(void *ptr) {
    int *value = ptr;

    CIMUNIT_THREAD_NAME("z");
    CIMUNIT_FIRE("c1");
    *value *= 4;
    CIMUNIT_FIRE("c2");
}


static void test_cimunit_thread_condition_thread(void)
{
    cimunit_thread_t threadA;
    cimunit_thread_t threadB;
    int value = 1;
    
    // Create schedule
    CIMUNIT_SCHEDULE("a2@x->b1");

    // Create and execute threads
    cimunit_thread_create(&threadA, test_macro_eventA_threadZ, (void *)&value);
    cimunit_thread_create(&threadB, test_macro_eventB_threadY, (void *)&value);


    cimunit_thread_join(threadA, NULL);
    cimunit_thread_sleep(100);

    CU_ASSERT_EQUAL(value, 2);

    value = 1;
    cimunit_thread_create(&threadA, test_macro_eventA_threadX, (void *)&value);

    cimunit_thread_join(threadA, NULL);
    cimunit_thread_join(threadB, NULL);

    CU_ASSERT_EQUAL(value, 5);
}


static void test_cimunit_thread_wrong_action_thread(void)
{
    cimunit_thread_t threadA;
    int value = 1;
    
    // Create schedule
    CIMUNIT_SCHEDULE("b2@y->a1@x");

    // Create and execute threads
    cimunit_thread_create(&threadA, test_macro_eventA_threadZ, (void *)&value);

    cimunit_thread_join(threadA, NULL);

    // Verify SUT
    CU_ASSERT_EQUAL(value, 2);
}


static void test_cimunit_thread_right_action_thread(void)
{
    cimunit_thread_t threadA;
    cimunit_thread_t threadB;
    int value = 1;
    
    // Create schedule
    CIMUNIT_SCHEDULE("a2@x->b1@y");

    // Create and execute threads
    cimunit_thread_create(&threadA, test_macro_eventA_threadX, (void *)&value);
    cimunit_thread_create(&threadB, test_macro_eventB_threadY, (void *)&value);


    cimunit_thread_join(threadA, NULL);
    cimunit_thread_join(threadB, NULL);

    CU_ASSERT_EQUAL(value, 5);
}


static void test_cimunit_thread_unnamed_condition_thread(void)
{
    cimunit_thread_t threadA;
    cimunit_thread_t threadB;
    int value = 1;
    
    // Create schedule
    CIMUNIT_SCHEDULE("a2->b1@y");

    // Create and execute threads
    cimunit_thread_create(&threadA, test_macro_eventA_threadX, (void *)&value);
    cimunit_thread_create(&threadB, test_macro_eventB_threadY, (void *)&value);


    cimunit_thread_join(threadA, NULL);
    cimunit_thread_join(threadB, NULL);

    CU_ASSERT_EQUAL(value, 5);
}


static CU_TestInfo tests_cimunit[] = {
  {"basic1", test_cimunit_basic1},
  {"basic2", test_cimunit_basic2},
  {"macro basic1", test_cimunit_macro_basic1},
  {"macro basic2", test_cimunit_macro_basic2},
  {"macro two actions 1", test_cimunit_macro_two_actions1},
  {"macro two actions 1a", test_cimunit_macro_two_actions1a},
  {"macro two actions 2", test_cimunit_macro_two_actions2},
  {"macro two actions 2a", test_cimunit_macro_two_actions2a},
  {"macro or conditional 1", test_cimunit_macro_or_conditional1},
  {"macro or conditional 2", test_cimunit_macro_or_conditional2},
  {"macro and conditional 1", test_cimunit_macro_and_conditional1},
  {"macro and conditional 2", test_cimunit_macro_and_conditional2},
  {"thread wrong and right condition thread", test_cimunit_thread_condition_thread},
  {"thread wrong action thread", test_cimunit_thread_wrong_action_thread},
  {"thread right action thread", test_cimunit_thread_right_action_thread},
  {"thread unnamed condition thread", test_cimunit_thread_unnamed_condition_thread},
  CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  {"suite_cimunit_schedule", NULL, NULL, tests_cimunit},
  CU_SUITE_INFO_NULL,
};

RUN_TEST_SUITES(suites, test_cimunit);
