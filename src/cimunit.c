#include "cimunit.h"
#include "cimunit_thread.h"
#include <stdio.h>

int cimunit_run_test(void *(*test_func)(void *), cimunit_schedule_t *sc){
  cimunit_thread_id_t i;
  cimunit_thread_t *threads = 
    (cimunit_thread_t*)malloc(sizeof(cimunit_thread_t)*(sc->numThreads));
  cimunit_test_args_t *args = 
    (cimunit_test_args_t*)malloc(sizeof(cimunit_test_args_t)*(sc->numThreads));
  
  for(i=0;i<sc->numThreads;++i){
    args[i].schedule = sc;
    args[i].thread = i;
    cimunit_thread_create(&(threads[i]), NULL, test_func, (void*)(&(args[i]))); 
  }

  for(i=0;i<sc->numThreads; ++i){
    //TODO, instead of null we'll actually wanna look at the return value.
    cimunit_join(threads[i], NULL);
  }
  free(threads);
  free(args);
}


int cimunit_run_tests(cimunit_tester_t *tester){
  cimunit_test_instance_t *nextTest = tester->headTest;
  while(nextTest != NULL){
    if(nextTest == NULL){
      printf("Next test was null\n");
    }
    if(nextTest->test_func == NULL){
      printf("fucn was null\n");
    }
    if(nextTest->sc == NULL){
      printf("schedule was null\n");
    }
    cimunit_run_test(nextTest->test_func, nextTest->sc);
    nextTest = nextTest->next;
  }
}
