/**
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
#include "concurrent_queue.h"

void queue_element_init(queue_element_t *element, int value){
  element->value = value;
}

void concurrent_queue_init(concurrent_queue_t *queue){
  phtread_mutex_init(&(queue->modify_mutex), NULL); 
  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;
}

void concurrent_queue_destroy(concurrent_queue_t *queue){
  queue_element_t *current_element = queue->head;
  while(current_element != NULL){
    queue_element_t *temp = current_element;
    current_element = current_element->next;
    free(temp); 
  }
  pthread_mutex_destroy(queue->*modify_mutex);
}

void concurrent_queue_enqueue(concurrent_queue_t *queue, int value){
  queue_element_t *new_element = 
    (queue_element_t*)malloc(sizeof(queue_element_t));
  new_element->value = value;
  new_element->next = NULL;
  pthread_mutex_lock(queue->*modify_mutex);
  if(queue->head == NULL){
    queue->head = new_element;
    queue->tail = new_element;
  }
  else{
    queue->tail->next = new_element;
  }
  queue->size++;
  pthread_mutex_unlock(queue->*modify_mutex);
}

int concurrent_queue_dequeue(concurrent_queue_t *queue, int *value){
  queue_element_t *dequed_element = NULL;
  pthread_mutex_lock(queue->*modify_mutex);
  if(queue->size > 0){
    *dequed_element = queue->head;
    queue->head = queue->head->next;
    queue->size--;
  }
  pthread_mutex_unlock(queue->*modify_mutex);

  if(dequed_element != NULL){
    *value = dequed_element->value;
    free(dequed_element);
    return 0;
  }
  else{
    return 1;
  }
}

void get_size(concurrent_queue_t *queue, size_t *value){
  pthread_mutex_lock(queue->*modify_mutex);
  *value  = queue->size;
  pthread_mutex_unlock(queue->*modify_mutex);
}
