/**
 * \file cimunit_thread_table.c
 *
 * Copyright 2011 Dale Frampton and Kurtis Nusbaum
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
#include "cimunit_thread_table.h"
#include <string.h>
#include <stdlib.h>

int cimunit_thread_table_element_init(
  cimunit_thread_table_element_t *thread_table_element,
  cimunit_thread_t thread,
  const char *name)
{
  thread_table_element->thread = thread;
  thread_table_element->name = name;
  thread_table_element->next = NULL;
  return 0;
}


int cimunit_thread_table_element_destroy(
  cimunit_thread_table_element_t *thread_table_element)
{
  //this is a no op for now...
  return 0;
}


int cimunit_thread_table_init(cimunit_thread_table_t *thread_table){
  thread_table->head = NULL;
  return 0;
}


int cimunit_thread_table_destroy(cimunit_thread_table_t *thread_table){
  cimunit_thread_table_element_t *next_element = thread_table->head;
  while(next_element != NULL){
    cimunit_thread_table_element_t *temp = next_element;  
    next_element  = next_element->next;
    cimunit_thread_table_element_destroy(temp);
    free(temp);
  }
  //Actually return something else if an error occurs
  return 0; 
}

int cimunit_find_thread_in_table(
  const cimunit_thread_table_t *thread_table,
  cimunit_thread_t thread,
  cimunit_thread_table_element_t **found_element)
{
  *found_element = NULL;
  cimunit_thread_table_element_t *current_element = thread_table->head;
  while(current_element != NULL){
    if(current_element->thread == thread){
      *found_element = current_element;
       return 0;
    }
    else{
      current_element = current_element->next;
    }
  }
  return 0;
}


int cimunit_set_thread_name(
  cimunit_thread_table_t *thread_table,
  cimunit_thread_t thread,
  const char *name)
{
  cimunit_thread_table_element_t *thread_table_element = NULL;
  cimunit_find_thread_in_table(thread_table, thread, &thread_table_element);
  if(thread_table_element == NULL){
    thread_table_element = (cimunit_thread_table_element_t*)malloc(
      sizeof(cimunit_thread_table_element_t));
    cimunit_thread_table_element_init(thread_table_element, thread, name);
    thread_table_element->next = thread_table->head;
    thread_table->head = thread_table_element;
  }
  else{
    thread_table_element->name = name;
  }
  //TODO actually return error code;
  return 0;
}


int cimunit_get_thread_name(
  const cimunit_thread_table_t *thread_table,
  cimunit_thread_t thread,
  const char **buf)
{
  cimunit_thread_table_element_t *thread_table_element = NULL;
  cimunit_find_thread_in_table(thread_table, thread, &thread_table_element);
  if (thread_table_element)
  {
    *buf = thread_table_element->name;
  }
  return (thread_table_element != NULL);
}



