#include "cimunit.h"

int cimunit_run_test(int (*test_func)(void *), cimunit_schedule *sc){
  size_t i;
  CIMUNIT_THREAD* threads = 
    (CIMUNIT_THREAD*)malloc(sizeof(CIMUNIT_THREAD)*sc->numThreads);
  for(i=0;i<sc->numThreads;++i){
     
    
  }

}


int cimunit_run_tests(cimunit_test *tester){
  cimunit_test_instance *nextTest = tester->headTest;
  while(nextTest != NULL){
    cimunit_run_test(nextTest->test_function, nextTest->sc);
    nextTest = nextTest->next;
  }
}
