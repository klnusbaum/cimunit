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

/**
 * newTest should be null
 */
int cimunit_create_test_instance(
  int (*test_func)(void *),
  cimunit_schedule *sc,
  cimunit_test_instance *newTest )
{
  cimunit_test_instance *newTest = (cimunit_test_instance*)malloc(
    sizeof(cimunit_test_instance));
  newTest->test_function = test_func;
  newTest->sc = sc;
  newTest->next = NULL;
}

cimunit_queue_test(
  cimunit_test_instance* newTest, 
  cimunit_tester *tester)
{
  if(headTest == NULL){
    headTest = newTest;
    tailTest = tailTest;
  }
  else{
    tailTest->next = newTest;
    tailTest = newTest;
  }
}

int cimunit_add_test(
  cimunit_tester *tester, 
  int (*test_func)(void *),
  cimunit_schedule* sc )
{
  cimunit_test_instance *newTest;
  cimunit_create_test_instance(test_func, sc, newTest);
  cimunit_queue_test(newTest, tester);
}

