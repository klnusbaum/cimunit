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

#ifndef CIMUNIT_TESTER_H
#define CIMUNIT_TESTER_H
#include "cimunit_schedule.h"
typedef struct{
  int (*test_func)(void *) test_function;
  cimunit_schedule *sc;
  cimunit_test_instance *next;
}cimunit_test_instance;

/** \brief Struct which represent a sieres of tests to be run. */
typedef struct{
  cimunit_test_instance *headTest
  cimunit_test_instance *tailTest
} cimunit_tester tester;

int cimunit_add_test(
  cimunit_tester *tester, 
  int (*test_func)(void *),
  cimunit_schedule* sc );


#endif
