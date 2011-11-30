/**
 * \file cimunit_thread_table.h
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
#include "cimunit_thread_table.h"

/// \addtogroup cimunit_thread_table cimunit_thread_table Module
/// @{

/// Structure used to map a thread to the name of the thread
typedef struct cimunit_thread_table_element{
  cimunit_thread_t thread;
  const char *name;
  struct cimunit_thread_table_element *next;  
} cimunit_thread_table_element_t;

/// Structure serving as the entry point for the thread name list
typedef struct cimunit_thread_table {
  cimunit_thread_table_element_t *head;
} cimunit_thread_table_t;


/// Initialize a cimunit_thread_table_element object
/// \param thread_table_element - object to be initialized
/// \param thread - thread identifier that is being named
/// \param name - name given to the thread
int cimunit_thread_table_element_init(
  cimunit_thread_table_element_t *thread_table_element,
  cimunit_thread_t thread,
  const char *name);


/// Free a cimunit_thread_table_element object
/// \param thread_table_element - object to be destroyed
int cimunit_thread_table_element_destroy(
  cimunit_thread_table_element_t *thread_table_element);


/// Initialize a new cimunit_thread_table object
/// \param thread_table - object to be initialized
int cimunit_thread_table_init(cimunit_thread_table_t *thread_table);


/// Destroy a new cimunit_thread_table object
/// \param thread_table - object to be destroyed
int cimunit_thread_table_destroy(cimunit_thread_table_t *thread_table);


/// Name a thread
/// \param thread_table - table in which the name will be stored
/// \param thread - thread being named
/// \param name - name of the thread
int cimunit_set_thread_name(
  cimunit_thread_table_t *thread_table,
  cimunit_thread_t thread,
  const char *name);


/// Get the name of a thread
/// \param thread_table - table in which the name is stored
/// \param thread - thread whose name is being retrieved
/// \param buf - pointer to the char * where the name is stored
int cimunit_get_thread_name(
  const cimunit_thread_table_t *thread_table,
  cimunit_thread_t thread,
  const char **buf);

/// @}

#endif //CIMUNIT_THREAD_TABLE_H
