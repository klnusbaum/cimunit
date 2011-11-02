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

CIMUNIT_TEST(simple_test, test1){
  if(CIMUNIT_TNUMBER == 0){
    cimunit_schedule_fire(((cimunit_test_args_t*)args)->schedule,
                          "t1begin");
    printf("Hello from t1\n");
    cimunit_schedule_fire(((cimunit_test_args_t*)args)->schedule,
                          "t1end");
  }
  else if(CIMUNIT_TNUMBER == 1){
    cimunit_schedule_fire(((cimunit_test_args_t*)args)->schedule,
                          "t2begin");
    printf("Hello from t2\n");
    cimunit_schedule_fire(((cimunit_test_args_t*)args)->schedule,
                          "t2end");
  }
}

int main(int argc, char *argv[]){

  cimunit_tester_t tester;
  cimunit_init_tester(&tester);

  cimunit_schedule_t *sched1 = cimunit_schedule_parse("t1end->t2begin");
  CIMUNIT_ADD_TEST_SCHEDULE(tester, simple_test, test1, sched1, 2)

  return cimunit_run_tests(&tester);
}

