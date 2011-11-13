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

#ifndef CIMUNIT_THREAD_TABLE_H
#define CIMUNIT_THREAD_TABLE_H
#include "cimunit_thread.h"

typedef struct cimunit_thread_table_element{
  cimunit_thread_t thread;
  const char* name;
  struct cimunit_thread_table_element *next;  
} cimunit_thread_table_element_t;

typedef struct{
  cimunit_thread_table_element_t *head;
} cimunit_thread_table_t;


int cimunit_thread_table_element_init(
  cimunit_thread_table_element_t *thread_table_element,
  cimunit_thread_t thread,
  const char *name);

int cimunit_thread_table_element_destroy(
  cimunit_thread_table_element_t *thread_table_element);

int cimunit_thread_table_init(cimunit_thread_table_t *thread_table);

int cimunit_thread_table_destroy(cimunit_thread_table_t *thread_table);

int cimunit_set_thread_name(
  cimunit_thread_table_t *thread_table,
  cimunit_thread_t thread,
  const char *name);

int cimunit_get_thread_name(
  const cimunit_thread_table_t *thread_table,
  cimunit_thread_t thread,
  const char **buf);

#endif //CIMUNIT_THREAD_TABLE_H
