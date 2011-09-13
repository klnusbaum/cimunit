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

#include "cimunit.h"

CIMUNIT_TEST(simple_test, test1){
  if(CIMUNIT_TNUMBER == 0){
    CIMUNIT_FIRE_EVENT(t1begin) 
    printf("Hello from t1\n");
    CIMUNIT_FIRE_EVENT(t1end)
  }
  else if(CIMUNIT_TNUMBER == 1){
    CIMUNIT_FIRE_EVENT(t2begin)
    printf("Hello from t2\n");
    CIMUNIT_FIRE_EVENT(t2end)
  }
}

int main(int argv, char *argv[]){

  cimunit_tester_t tester;

  cimunit_schedule_t sched1;
  cimunit_schedule_t sched2;
  cimunit_init_schedule(&sched1, "t1end->t2begin", 2);
  //cimunit_init_schedule(&sched2, "t2end->t1begin", 2);
  
  CIMUNIT_ADD_TEST_SCHEDULE(tester, simple_test, test1, sched1)
  CIMUNIT_ADD_TEST_SCHEDULE(tester, simple_test, test1, sched2)

  return cimunit_run_tests(tester);
}

