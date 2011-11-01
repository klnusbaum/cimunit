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
#ifndef CIMUNIT_EVENT_TABLE_H
#define CIMUNIT_EVENT_TABLE_H
#include "cimunit_event.h"
#include "cimunit_thread.h"

/// Structure defining a CIMUnit event table entry.
typedef struct event_table_entry{
  /// The a pointer to the event that is being represented by this entry.
  cimunit_event_t *event;

  /// The thread id of the thread that fired the event
  cimunit_thread_t thread;

  /// The next event in the cimunit_event_table. This is here since
  /// each entry in the event table is the member of a linked list.
  /// By default, next is NLLL.
  struct event_table_entry *next;
} cimunit_event_table_entry_t;

/// A table representing all the events that have been fired in a particular
/// CIMUnit test.
typedef struct cimunit_event_table {

  /// The head table entry. Is initially NULL.
  cimunit_event_table_entry_t *head;

  /// The tail table entry. Is initially NULL.
  cimunit_event_table_entry_t *tail;

  /// The lock that needs to be aquired before making any modifications to the
  /// table.
  cimunit_mutex_t lock;
} cimunit_event_table_t;


/// Initializes and event table entry
///
/// \param entry - entry to initialize
/// \param event - event this entry is representing
/// \returns = 0 if the call was succesful, otherwise an error code.
int cimunit_event_table_entry_init(
  cimunit_event_table_entry_t *entry,
  cimunit_event_t *event);

/// Frees all alocated resources for the event table entry
///
/// \param entry - Entry to destroy.
/// \return - 0 if the destruction was succesfull, false otherwise.
int cimunit_event_table_entry_destroy(cimunit_event_table_entry_t *entry);

/// Initializes an event table
///
/// \param event_table - Table to initialize.
/// \returns - 0 if the initialization was succesfull, error code otherwise.
int cimunit_event_table_init(cimunit_event_table_t *event_table);

/// Frees all allocated resources for the CIMUnit Event Table.
///
/// \param event_table - Event table to destroy
/// \return - 0 if succesful error code otherwise.
int cimunit_event_table_destroy(cimunit_event_table_t *event_table);

/// Adds and event entry to the table
///
/// \param event_table - Table to which the event should be added.
/// \param event - The event to be added.
/// \param entry_added - Once the event is added, this will point to the
///  new event table entry that was added. This parameter may be NULL.
/// \return - 0 if succesfull, error code otherwise.
int cimunit_add_event_to_table(
  cimunit_event_table_t *event_table,
  cimunit_event_t *event,
  cimunit_event_table_entry_t **entry_added);

/// Finds a given event in the table, regardless of what thread fired it.
///
/// \param event_table - Table to search.
/// \param event_name - Name of event to search for.
/// \param found_event - If the event is found, the pointer this parameter
/// points to will be populated with first event_entry that matches the search
/// criteria. If no event is found, the pointer will be set to pointing at NULL.
///
/// \return - 0 if the function executed sucessfully, error code otherwise
///
int cimunit_find_event_in_table(
  const cimunit_event_table_t *event_table,
  const char *event_name,
  cimunit_event_table_entry_t **found_event);

/// Finds a given event in the table, regardless of what thread fired it.
/// Lord forgive this O(n) search.
///
/// \param event_table - Table to search.
/// \param event_name - Name of event to search for.
/// \param thread_name - Name of the thread for which the event is desired to 
///  have fired on.
/// \param found_event - If the event is found, the pointer this parameter
/// points to will be populated with first event_entry that matches the search
/// criteria. If no event is found, the pointer will be set to pointing at NULL.
///
/// \return - 0 if the function executed sucessfully, error code otherwise
///
int cimunit_find_event_in_table_on_thread(
  const cimunit_event_table_t *event_table,
  const char *event_name,
  const char *thread_name,
  cimunit_event_table_entry_t **found_event);


#endif
