#include "cimunit.h"

int main(int argc, char* argv[]){
  cimunit_schedule_t test_schedule;
  cimunit_init_schedule(&test_schedule, "t1end->t2begin", 2);
  cimunit_event_t *found = NULL;
  cimunit_get_schedule_event("t1end", &test_schedule, found);
  if(found == NULL){
    return 1;
  }
  else{
    return 0;
  }
}
