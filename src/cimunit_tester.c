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
#include "cimunit_tester.h"
#include <stdio.h>

/**
 * newTest should be null
 */
int cimunit_init_test_instance(
  void *(*test_func)(void *),
  cimunit_schedule_t *sc,
  cimunit_test_instance_t *newTest )
{
  newTest->test_func = test_func;
  newTest->sc = sc;
  newTest->next = NULL;
}

int cimunit_init_tester(cimunit_tester_t *toInit){
  toInit->headTest = NULL;
  toInit->tailTest = NULL;
}

int cimunit_queue_test(
  cimunit_test_instance_t *newTest, 
  cimunit_tester_t *tester)
{
  if(tester->headTest == NULL){
    tester->headTest = newTest;
    tester->tailTest = newTest;
  }
  else{
    tester->tailTest->next = newTest;
    tester->tailTest = newTest;
  }
}

int cimunit_add_test(
  cimunit_tester_t *tester, 
  void *(*test_func)(void *),
  cimunit_schedule_t* sc )
{
  cimunit_test_instance_t *newTest = 
    (cimunit_test_instance_t*)malloc(sizeof(cimunit_test_instance_t));
  cimunit_init_test_instance(test_func, sc, newTest);
  cimunit_queue_test(newTest, tester);
}

