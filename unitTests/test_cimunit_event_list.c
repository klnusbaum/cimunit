/*
 * \file test_cimunit_event_list.c
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

#include "testMain.h"
#include "cimunit_event_list.h"


static void test_cimunit_init_event_list(void)
{
    CU_ASSERT_PTR_NULL(cimunit_event_list_init());
}


static void test_cimunit_add_event_list(void)
{
    cimunit_event_list_t *list = cimunit_event_list_init();
    cimunit_event_t event;
    cimunit_event_init(&event, "a");
    
    cimunit_event_list_add(&list, &event);
    CU_ASSERT_PTR_NOT_NULL(list);
    CU_ASSERT_PTR_EQUAL(list->event, &event);
    
    cimunit_event_list_destroy(&list);
    CU_ASSERT_PTR_NULL(list);
}


static void test_cimunit_event_list_find_empty(void) {
    CU_ASSERT_PTR_NULL(cimunit_event_list_find(NULL, "a"));
}


static void test_cimunit_event_list_find_missing(void) {
    cimunit_event_list_t *list = cimunit_event_list_init();
    cimunit_event_t event1;
    cimunit_event_init(&event1, "a");
    cimunit_event_t event2;
    cimunit_event_init(&event2, "b");
    cimunit_event_list_add(&list, &event2);
    cimunit_event_list_add(&list, &event1);
    
    CU_ASSERT_PTR_NULL(cimunit_event_list_find(list, "c"));
    cimunit_event_list_destroy(&list);
    cimunit_event_destroy(&event1);
    cimunit_event_destroy(&event2);
}


static void test_cimunit_event_list_find_first(void) {
    cimunit_event_list_t *list = cimunit_event_list_init();
    cimunit_event_t event1;
    cimunit_event_init(&event1, "a");
    cimunit_event_t event2;
    cimunit_event_init(&event2, "b");
    cimunit_event_list_add(&list, &event2);
    cimunit_event_list_add(&list, &event1);
    
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(list, "a"));
    cimunit_event_list_destroy(&list);
    cimunit_event_destroy(&event1);
    cimunit_event_destroy(&event2);
}


static void test_cimunit_event_list_find_second(void) {
    cimunit_event_list_t *list = cimunit_event_list_init();
    cimunit_event_t event1;
    cimunit_event_init(&event1, "a");
    cimunit_event_t event2;
    cimunit_event_init(&event2, "b");
    cimunit_event_list_add(&list, &event2);
    cimunit_event_list_add(&list, &event1);
    
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(list, "b"));
    cimunit_event_list_destroy(&list);
    cimunit_event_destroy(&event1);
    cimunit_event_destroy(&event2);
}


static void test_cimunit_event_list_merge_empty_first(void) {
    cimunit_event_list_t *list = cimunit_event_list_init();
    cimunit_event_t event1;
    cimunit_event_init(&event1, "a");
    cimunit_event_t event2;
    cimunit_event_init(&event2, "b");
    cimunit_event_list_add(&list, &event2);
    cimunit_event_list_add(&list, &event1);

    cimunit_event_list_t *new_list = cimunit_event_list_init();

    cimunit_event_list_union(&new_list, list);
    CU_ASSERT_PTR_NOT_NULL(new_list);
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(new_list, "a"));
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(new_list, "b"));

    cimunit_event_list_destroy(&list);
    cimunit_event_destroy(&event1);
    cimunit_event_destroy(&event2);
}


static void test_cimunit_event_list_merge_empty_second(void) {
    cimunit_event_list_t *list = cimunit_event_list_init();
    cimunit_event_t event1;
    cimunit_event_init(&event1, "a");
    cimunit_event_t event2;
    cimunit_event_init(&event2, "b");
    cimunit_event_list_add(&list, &event2);
    cimunit_event_list_add(&list, &event1);

    cimunit_event_list_t *new_list = cimunit_event_list_init();

    cimunit_event_list_union(&list, new_list);
    CU_ASSERT_PTR_NOT_NULL(list);
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(list, "a"));
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(list, "b"));

    cimunit_event_list_destroy(&list);
    cimunit_event_destroy(&event1);
    cimunit_event_destroy(&event2);
}


static void test_cimunit_event_list_merge_duplicate(void) {
    cimunit_event_list_t *list = cimunit_event_list_init();
    cimunit_event_list_t *list2 = cimunit_event_list_init();
    cimunit_event_t event1;
    cimunit_event_init(&event1, "a");
    cimunit_event_list_add(&list, &event1);
    cimunit_event_list_add(&list2, &event1);

    cimunit_event_list_union(&list, list2);
    CU_ASSERT_PTR_NOT_NULL(list);
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(list, "a"));
    CU_ASSERT_PTR_NULL(list->next);
    cimunit_event_list_destroy(&list);
    cimunit_event_list_destroy(&list2);
    cimunit_event_destroy(&event1);
}


static void test_cimunit_event_list_merge(void) {
    cimunit_event_list_t *list = cimunit_event_list_init();
    cimunit_event_t event1;
    cimunit_event_init(&event1, "a");
    cimunit_event_list_add(&list, &event1);

    cimunit_event_list_t *list2 = cimunit_event_list_init();
    cimunit_event_t event2;
    cimunit_event_init(&event2, "b");
    cimunit_event_list_add(&list2, &event2);

    cimunit_event_list_union(&list, list2);
    CU_ASSERT_PTR_NOT_NULL(list);
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(list, "a"));
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find(list, "b"));
    cimunit_event_list_destroy(&list);
    cimunit_event_list_destroy(&list2);
    cimunit_event_destroy(&event1);
    cimunit_event_destroy(&event2);
}


static void test_cimunit_event_list_without_thread(void) {
    cimunit_event_list_t *list = cimunit_event_list_init();
    cimunit_event_t event1;
    cimunit_event_init(&event1, "a");
    cimunit_event_t event2;
    cimunit_event_init(&event2, "b");
    cimunit_event_list_add(&list, &event2);
    cimunit_event_list_add(&list, &event1);

    printf("==\n");
    
    CU_ASSERT_PTR_NULL(cimunit_event_list_find_with_thread(
                         list, "a", "x"));
    printf("==\n");
    cimunit_event_list_destroy(&list);
    cimunit_event_destroy(&event1);
    cimunit_event_destroy(&event2);

}


static void test_cimunit_event_list_with_thread(void) {
    cimunit_event_list_t *list = cimunit_event_list_init();
    cimunit_event_t event1;
    cimunit_event_init_with_thread(&event1, "a", "x");
    cimunit_event_t event2;
    cimunit_event_init(&event2, "b");
    cimunit_event_list_add(&list, &event2);
    cimunit_event_list_add(&list, &event1);
    
    CU_ASSERT_PTR_NOT_NULL(cimunit_event_list_find_with_thread(
                             list, "a", "x"));
    cimunit_event_list_destroy(&list);
    cimunit_event_destroy(&event1);
    cimunit_event_destroy(&event2);

}


static CU_TestInfo tests_cimunit_event[] = {
  {"init", test_cimunit_init_event_list},
  {"add event", test_cimunit_add_event_list},
  {"find empty event list", test_cimunit_event_list_find_empty},
  {"find missing event", test_cimunit_event_list_find_missing},
  {"find first event", test_cimunit_event_list_find_first},
  {"find second event", test_cimunit_event_list_find_second},
  {"merge empty first list", test_cimunit_event_list_merge_empty_first},
  {"merge empty second list", test_cimunit_event_list_merge_empty_second},
  {"merge duplicate list", test_cimunit_event_list_merge_duplicate},
  {"merge", test_cimunit_event_list_merge},
  {"find event without thread", test_cimunit_event_list_without_thread},
  {"find event with thread", test_cimunit_event_list_with_thread},
  CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  {"suite_cimunit_event", NULL, NULL, tests_cimunit_event},
  CU_SUITE_INFO_NULL,
};

RUN_TEST_SUITES(suites)
