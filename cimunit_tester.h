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
