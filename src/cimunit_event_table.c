#include <stdlib.h>
#include <string.h>
#include "cimunit_event_table.h"
#include "cimunit_platform.h"

int cimunit_event_table_entry_init(
  cimunit_event_table_entry_t *entry,
  cimunit_event_t *event)
{
  entry->event = event;
  entry->thread = cimunit_thread_self();
  entry->next = NULL; 
  //TODO actually return the correct error code if an error happend.
  return 0;
}

int cimunit_event_table_entry_destroy(cimunit_event_table_entry_t *entry){
  //this is a no-op at the moment
}

int cimunit_event_table_init(
  cimunit_event_table_t *event_table, 
  const cimunit_thread_table_t *thread_table)
{
  event_table->head = NULL;
  event_table->tail = NULL;
  event_table->thread_table = thread_table;
  cimunit_mutex_init(&(event_table->lock), NULL);
  //TODO actually return the correct error code if an error happend.
  return 0;
}

int cimunit_event_table_destroy(cimunit_event_table_t *event_table){
  cimunit_event_table_entry_t *current_entry = event_table->head;
  while(current_entry != NULL){
    event_table->head = current_entry->next;
    cimunit_event_table_entry_destroy(current_entry);
    free(current_entry);
    current_entry = event_table->head;
  }
  cimunit_mutex_destroy(&(event_table->lock));
  //TODO actually return the correct error code if an error happend.
  return 0;
}

int cimunit_add_event_to_table(
  cimunit_event_table_t *event_table,
  cimunit_event_t *event,
  cimunit_event_table_entry_t **entry_added)
{
  cimunit_event_table_entry_t *new_entry = 
    (cimunit_event_table_entry_t*)malloc(sizeof(cimunit_event_table_entry_t));
  cimunit_event_table_entry_init(new_entry, event);
  cimunit_mutex_lock(&(event_table->lock));
  if(event_table->head == NULL){
    event_table->head = new_entry;
    event_table->tail = new_entry;
  }  
  else{
    event_table->tail->next = new_entry;
    event_table->tail = new_entry;
  }
  cimunit_mutex_unlock(&(event_table->lock));

  if(entry_added != NULL){
    (*entry_added) = new_entry;
  }
  //TODO actually return the correct error code if an error happend.
  return 0;
}

int cimunit_event_matches_table_entry(
  const cimunit_event_table_entry_t* table_entry,
  const cimunit_thread_table_t *thread_table,
  const char *event_name,
  const char *thread_name)
{
  const char *thread_name_buffer;
  cimunit_get_thread_name(
    thread_table,
    table_entry->thread, 
    &thread_name_buffer);

  if (!strcmp(table_entry->event->event_name, event_name)) {
    if (thread_name) {
        return (thread_name_buffer &&
                !strcmp(thread_name_buffer, thread_name));
    } else {
        return TRUE;
    }
  }
  
  return FALSE;
}

int cimunit_find_event_in_table(
  const cimunit_event_table_t *event_table,
  const char *event_name,
  cimunit_event_table_entry_t **found_event)
{
  return cimunit_find_event_in_table_on_thread(
    event_table,
    event_name,
    NULL,
    found_event);
}

//Lord forgive this O(n) search
int cimunit_find_event_in_table_on_thread(
  const cimunit_event_table_t *event_table,
  const char *event_name,
  const char *thread_name,
  cimunit_event_table_entry_t **found_event)
{
  (*found_event) = event_table->head;
  while((*found_event) != NULL){
    if(cimunit_event_matches_table_entry(
      *found_event, event_table->thread_table,
       event_name, 
       thread_name))
    {
      break;
    }    
    (*found_event) = (*found_event)->next;
  }
  //TODO actually return the correct error code if an error happend.
  return 0;
}




