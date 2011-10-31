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
#include <assert.h>

#include "testMain.h"
#include "cimunit.h"


struct test_event_args {
    cimunit_schedule_t *schedule;
    int *value;
};

static void *test_eventA(void *ptr) {
    struct test_event_args *args = ptr;
    cimunit_fire(args->schedule, "a");
    *args->value *= 2;
}

static void *test_eventB(void *ptr) {
    struct test_event_args *args = ptr;
    cimunit_fire(args->schedule, "b");
    *args->value += 3;
}


static void test_cimunit_basic1(void)
{
    // Create schedule
    cimunit_schedule_t *schedule = cimunit_schedule_parse("a->b");
    int value = 1;

    // Pass data to threads
    struct test_event_args args;
    args.schedule = schedule;
    args.value = &value;
    
    // Create and execute threads
    pthread_t threadA;
    pthread_t threadB;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threadA, &attr, test_eventA, (void *)&args);
    pthread_create(&threadB, &attr, test_eventB, (void *)&args);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    // Clean up threading
    pthread_attr_destroy(&attr);
    
    // Verify SUT
    CU_ASSERT_EQUAL(value, 5);

    // Cleanup schedule
    cimunit_schedule_destroy(schedule);
}


static void test_cimunit_basic2(void)
{
    // Create schedule
    cimunit_schedule_t *schedule = cimunit_schedule_parse("b->a");
    int value = 1;

    // Pass data to threads
    struct test_event_args args;
    args.schedule = schedule;
    args.value = &value;
    
    // Create and execute threads
    pthread_t threadA;
    pthread_t threadB;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threadA, &attr, test_eventA, (void *)&args);
    pthread_create(&threadB, &attr, test_eventB, (void *)&args);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    // Clean up threading
    pthread_attr_destroy(&attr);
    
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
    // Create schedule
    CIMUNIT_SCHEDULE("a2->b1");
    int value = 1;

    // Create and execute threads
    pthread_t threadA;
    pthread_t threadB;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threadA, &attr, test_macro_eventA, (void *)&value);
    pthread_create(&threadB, &attr, test_macro_eventB, (void *)&value);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    // Clean up threading
    pthread_attr_destroy(&attr);
    
    // Verify SUT
    CU_ASSERT_EQUAL(value, 5);
}


static void test_cimunit_macro_basic2(void)
{
    // Create schedule
    CIMUNIT_SCHEDULE("b2->a1");
    int value = 1;

    // Create and execute threads
    pthread_t threadA;
    pthread_t threadB;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threadA, &attr, test_macro_eventA, (void *)&value);
    pthread_create(&threadB, &attr, test_macro_eventB, (void *)&value);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    // Clean up threading
    pthread_attr_destroy(&attr);
    
    // Verify SUT
    CU_ASSERT_EQUAL(value, 8);
}


static void test_cimunit_macro_two_actions1(void)
{
    // Create schedule
    CIMUNIT_SCHEDULE("a2->b1,b2->c1");
    int value = 1;

    // Create and execute threads
    pthread_t threadA;
    pthread_t threadB;
    pthread_t threadC;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threadA, &attr, test_macro_eventA, (void *)&value);
    pthread_create(&threadB, &attr, test_macro_eventB, (void *)&value);
    pthread_create(&threadC, &attr, test_macro_eventC, (void *)&value);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    // Clean up threading
    pthread_attr_destroy(&attr);
    
    // Verify SUT
    CU_ASSERT_EQUAL(value, 20);
}



static void test_cimunit_macro_two_actions1a(void)
{
    // Create schedule
    CIMUNIT_SCHEDULE("b2->c1,a2->b1");
    int value = 1;

    // Create and execute threads
    pthread_t threadA;
    pthread_t threadB;
    pthread_t threadC;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threadA, &attr, test_macro_eventA, (void *)&value);
    pthread_create(&threadB, &attr, test_macro_eventB, (void *)&value);
    pthread_create(&threadC, &attr, test_macro_eventC, (void *)&value);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    // Clean up threading
    pthread_attr_destroy(&attr);
    
    // Verify SUT
    CU_ASSERT_EQUAL(value, 20);
}


static void test_cimunit_macro_two_actions2(void)
{
    // Create schedule
    CIMUNIT_SCHEDULE("c2->b1,b2->a1");
    int value = 1;

    // Create and execute threads
    pthread_t threadA;
    pthread_t threadB;
    pthread_t threadC;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threadA, &attr, test_macro_eventA, (void *)&value);
    pthread_create(&threadB, &attr, test_macro_eventB, (void *)&value);
    pthread_create(&threadC, &attr, test_macro_eventC, (void *)&value);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    // Clean up threading
    pthread_attr_destroy(&attr);
    
    // Verify SUT
    CU_ASSERT_EQUAL(value, 14);
}


static void test_cimunit_macro_two_actions2a(void)
{
    // Create schedule
    CIMUNIT_SCHEDULE("b2->a1,c2->b1");
    int value = 1;

    // Create and execute threads
    pthread_t threadA;
    pthread_t threadB;
    pthread_t threadC;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threadA, &attr, test_macro_eventA, (void *)&value);
    pthread_create(&threadB, &attr, test_macro_eventB, (void *)&value);
    pthread_create(&threadC, &attr, test_macro_eventC, (void *)&value);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    // Clean up threading
    pthread_attr_destroy(&attr);
    
    // Verify SUT
    CU_ASSERT_EQUAL(value, 14);
}


static void test_cimunit_macro_or_conditional1(void)
{
    // Create schedule
    CIMUNIT_SCHEDULE("b2||a2->c1");
    int value = 1;

    // Create and execute threads
    pthread_t threadB;
    pthread_t threadC;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threadC, &attr, test_macro_eventC, (void *)&value);
    pthread_create(&threadB, &attr, test_macro_eventB, (void *)&value);

    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    // Clean up threading
    pthread_attr_destroy(&attr);
    
    // Verify SUT
    CU_ASSERT_EQUAL(value, 16);
}


static void test_cimunit_macro_or_conditional2(void)
{
    // Create schedule
    CIMUNIT_SCHEDULE("a2||c2->b1");
    int value = 1;

    // Create and execute threads
    pthread_t threadA;
    pthread_t threadB;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threadA, &attr, test_macro_eventA, (void *)&value);
    pthread_create(&threadB, &attr, test_macro_eventB, (void *)&value);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    // Clean up threading
    pthread_attr_destroy(&attr);
    
    // Verify SUT
    CU_ASSERT_EQUAL(value, 5);
}


static void test_cimunit_macro_and_conditional1(void)
{
    // Create schedule
    CIMUNIT_SCHEDULE("b2&&a2->c1,a2->b1");
    int value = 1;

    // Create and execute threads
    pthread_t threadA;
    pthread_t threadB;
    pthread_t threadC;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threadC, &attr, test_macro_eventC, (void *)&value);
    pthread_create(&threadB, &attr, test_macro_eventB, (void *)&value);
    pthread_create(&threadA, &attr, test_macro_eventA, (void *)&value);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    // Clean up threading
    pthread_attr_destroy(&attr);
    
    // Verify SUT
    CU_ASSERT_EQUAL(value, 20);
}


static void test_cimunit_macro_and_conditional2(void)
{
    // Create schedule
    CIMUNIT_SCHEDULE("b2&&a2->c1,b2->a1");
    int value = 1;

    // Create and execute threads
    pthread_t threadA;
    pthread_t threadB;
    pthread_t threadC;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threadC, &attr, test_macro_eventC, (void *)&value);
    pthread_create(&threadB, &attr, test_macro_eventB, (void *)&value);
    pthread_create(&threadA, &attr, test_macro_eventA, (void *)&value);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    // Clean up threading
    pthread_attr_destroy(&attr);
    
    // Verify SUT
    CU_ASSERT_EQUAL(value, 32);
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
  CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  {"suite_cimunit_schedule", NULL, NULL, tests_cimunit},
  CU_SUITE_INFO_NULL,
};

void AddCimunitTests(void)
{
  assert(NULL != CU_get_registry());
  assert(!CU_is_test_running());

	/* Register suites. */
	if (CU_register_suites(suites) != CUE_SUCCESS) {
		fprintf(stderr, "suite registration failed - %s\n",
			CU_get_error_msg());
		exit(EXIT_FAILURE);
	}
}

RUN_TEST_SUITE(AddCimunitTests())
