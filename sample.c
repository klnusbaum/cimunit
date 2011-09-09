#include "cimunit.h"

CIMUNIT_TEST(simple_test, test1){
  if(CIMUNIT_TNUMBER == 0){
    CIMUNIT_FIRE_EVENT("t1begin") 
    printf("Hello from t1\n");
    CIMUNIT_FIRE_EVENT("t1end")
  }
  else if(CIMUNIT_TNUMBER == 1){
    CIMUNIT_FIRE_EVENT("t2begin")
    printf("Hello from t2\n");
    CIMUNIT_FIRE_EVENT("t2end")
  }
}

int main(int argv, char *argv[]){

  cimunit_tester tester;

  cimunit_schedule sched1;
  cimunit_schedule sched2;
  cimunit_init_schedule(&sched1, "t1end->t2begin", 2);
  cimunit_init_schedule(&sched2, "t2end->t1begin", 2);
  
  CIMUNIT_ADD_TEST_SCHEDULE(tester, simple_test, test1, sched1)
  CIMUNIT_ADD_TEST_SCHEDULE(tester, simple_test, test1, sched2)

  return cimunit_run_tests(tester);
}

