#include "cimunit.h"
#include <stdio.h>
int main(int argc, char *argv[]){
  const char* string = "t1end->t2begin";
  char *events[2];
  cimunit_get_event_names(string, events);
  printf("first %s\n", events[0]);
  printf("second %s\n", events[1]);
  return 0;
}
