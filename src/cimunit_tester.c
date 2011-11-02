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
#include <stdlib.h>

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
  cimunit_schedule_t* sc,
  size_t numThreads )
{
  cimunit_test_instance_t *newTest = 
    (cimunit_test_instance_t*)malloc(sizeof(cimunit_test_instance_t));
  cimunit_init_test_instance(test_func, sc, newTest);
  cimunit_queue_test(newTest, tester);
}


int cimunit_run_test(void *(*test_func)(void *), cimunit_schedule_t *sc,
                     size_t numThreads){
  cimunit_thread_id_t i;
  cimunit_thread_t *threads = 
    (cimunit_thread_t*)malloc(sizeof(cimunit_thread_t)*numThreads);
  cimunit_test_args_t *args = 
    (cimunit_test_args_t*)malloc(sizeof(cimunit_test_args_t)*numThreads);
  
  for(i=0;i<numThreads;++i){
    args[i].schedule = sc;
    args[i].thread = i;
    cimunit_thread_create(&(threads[i]), NULL, test_func, (void*)(&(args[i]))); 
  }

  for(i=0;i<numThreads; ++i){
    //TODO, instead of null we'll actually wanna look at the return value.
    cimunit_thread_join(threads[i], NULL);
  }
  free(threads);
  free(args);
}


int cimunit_run_tests(cimunit_tester_t *tester){
  cimunit_test_instance_t *nextTest = tester->headTest;
  while(nextTest != NULL){
    cimunit_run_test(nextTest->test_func, nextTest->sc, nextTest->numThreads);
    nextTest = nextTest->next;
  }
  cimunit_test_instance_t *to_dealloc;
  nextTest = tester->headTest;
  while(nextTest != NULL){
    to_dealloc = nextTest;
    nextTest = nextTest->next;
    free(to_dealloc);
  }

}
