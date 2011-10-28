#include <stdlib.h>
#include <string.h>
#include "cimunit_event_table.h"

int cimunit_init_event_table_entry(
  cimunit_event_table_entry_t *entry,
  cimunit_event_t *event)
{
  entry->event = event;
  entry->thread = cimunit_thread_self();
  entry->next = NULL; 
  //TODO actually return the correct error code if an error happend.
  return 0;
}

int cimunit_destroy_event_table_entry(cimunit_event_table_entry_t *entry){
  //this is a no-op at the moment
}

int cimunit_init_event_table(cimunit_event_table_t *event_table){
  event_table->head = NULL;
  event_table->tail = NULL;
  cimunit_mutex_init(&(event_table->lock), NULL);
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
  cimunit_init_event_table_entry(newEntry, event);
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

inline int cimunit_event_matches_table_entry(
  const cimunit_event_table_entry_t* table_entry,
  const char *event_name,
  const char *thread_name)
{
  char thread_name_buffer[CIMUNIT_MAX_THREAD_NAME_LENGTH];
  cimunit_thread_getname(table_entry->thread, thread_name_buffer);
  return
    strcmp(table_entry->event->event_name, event_name) &&
      (strcmp(CIMUNIT_DEFAULT_THREAD_NAME, thread_name)
      ||
      strcmp(thread_name_buffer, thread_name));
}

int cimunit_find_event_in_table(
  const cimunit_event_table_t *event_table,
  const char *event_name,
  const cimunit_event_table_entry_t **found_event)
{
  return cimunit_find_event_in_table_on_thread(
    event_table,
    event_name,
    CIMUNIT_DEFAULT_THREAD_NAME,
    found_event);
}

//Lord forgive this O(n) search
int cimunit_find_event_in_table_on_thread(
  const cimunit_event_table_t *event_table,
  const char *event_name,
  const char *thread_name,
  const cimunit_event_table_entry_t **found_event)
{
  (*found_event) = event_table->head;
  while(found_event != NULL){
    if(cimunit_event_matches_table_entry(*found_event, event_name, thread_name))
    {
      break;
    }    
    (*found_event) = (*found_event)->next;
  }
  //TODO actually return the correct error code if an error happend.
  return 0;
}


int cimunit_destroy_event_table(cimunit_event_table_t *event_table){
  cimunit_event_table_entry_t *current_entry = event_table->head;
  while(current_entry != NULL){
    event_table->head = current_entry->next;
    cimunit_destroy_event_table_entry(current_entry);
    free(current_entry);
    current_entry = event_table->head;
  }
  cimunit_mutex_destroy(&(event_table->lock));
  //TODO actually return the correct error code if an error happend.
  return 0;
}



