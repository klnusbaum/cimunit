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
#ifndef CIMUNIT_EVENT_TABLE
#define CIMUNIT_EVENT_TABLE

typedef struct event_table_entry{
  cimunit_event_t *event;
  cimunit_thread_t thread;
  event_table_entry *next;
} cimunit_event_table_entry_t;

typedef struct{
  cimunit_event_table_entry_t *head;
  cimunit_event_table_entry_t *tail;
  cimunit_mutex_t lock;
} cimunit_event_table_t;

int cimunit_init_event_table(cimunit_event_table_t *event_table);

int cimunit_create_event_table_entry(
  cimunit_event_table_entry_t *entry,
  cimunit_event *event);

int cimunit_add_event_to_table(
  cimunit_event_t *event;
  cimunit_event_table_entry_t *entry);

//lord forgive this O(n) search
//Returns the first event in the table with a matching name. Note that there
//might also be other events in this table that match the name but were fired
//on a different thread
//found_event will be null if not event matching the name is found
int cimunit_find_event_in_table(
  const cimunit_event_table_t *event_table,
  const char *event_name,
  const cimunit_event_table_entry_t *found_event);

int cimunit_find_event_in_table_on_thread(
  const cimunit_event_table_t *event_table,
  const char *event_name,
  const char *thread_name,
  const cimunit_event_table_entry_t *found_event);

#endif
