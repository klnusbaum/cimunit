#include "cimunit.h"
#include "cimunit_thread.h"

int cimunit_run_test(int (*test_func)(void *), cimunit_schedule *sc){
  size_t i;
  cimunit_thread *threads = 
    (cimunit_thread*)malloc(sizeof(cimunit_thread)*(sc->numThreads));
  cimunit_test_args *args = 
    (cimunit_test_args*)malloc(sizeof(cimunit_test_args)*(sc->numThreads));
  
  for(i=0;i<sc->numThreads;++i){
    args[i].schedule = sc
    args[i].thread = i;
    cimunit_thread_attr(&(threads[i]), NULL, test_func, (void*)(&(args[i]))); 
  }

  for(i=0;i<sc->numThreads; ++i){
    //TODO, instead of null we'll actually wanna look at the return value.
    cimunit_join(threads[i], NULL);
  }
  free(threads);
  free(args);
}


int cimunit_run_tests(cimunit_test *tester){
  cimunit_test_instance *nextTest = tester->headTest;
  while(nextTest != NULL){
    cimunit_run_test(nextTest->test_function, nextTest->sc);
    nextTest = nextTest->next;
  }
}
