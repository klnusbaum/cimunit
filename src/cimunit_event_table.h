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
  cimunit_thread_t *thread;
  short int hasFired;
  event_table_entry* next;
} cimunit_event_table_entry_t;

typedef struct{
  cimunit_event_table_entry_t *head;
  cimunit_event_table_entry_t *tail;
  cimunit_mutex_t lock;
} cimunit_event_table_t;

int cimunit_init_event_table(cimunit_event_table_t *event_table){
  event_table->head = NULL;
  event_table->tail = NULL;
  cimunit_mutex_init(&(event_table->lock), NULL);
}

int cimunit_add_event_to_table(
  cimunit_event_t *event;
  cimunit_event_table_entry_t *entry)
{
  cimunit_event_table_entry_t *newEntry = 
    (cimunit_event_table_entry_t*)malloc(sizeof(cimunit_event_table_entry_t)); 
  cimunit_mutex_lock(&(event_table->lock));
  if(event_table->head == NULL){
    

}

#endif
