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
#include "blocking_queue.h"

void queue_element_init(queue_element_t *element, int value){
  element->value = value;
}

void blocking_queue_init(blocking_queue_t *queue){
  phtread_mutex_init(&(queue->modify_mutex), NULL); 
  sem_init(&(queue->num_items_avail), 0, 0);
  queue->head = NULL;
  queue->tail = NULL;
}

void blocking_queue_destroy(blocking_queue_t *queue){
  queue_element_t *current_element = queue->head;
  while(current_element != NULL){
    queue_element_t *temp = current_element;
    current_element = current_element->next;
    free(temp); 
  }
  pthread_mutex_destroy(queue->*modify_mutex);
  sem_destroy(queue->*num_items_avail);
}

void blocking_queue_enqueue(blocking_queue_t *queue, int value){
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
  pthread_mutex_unlock(queue->*modify_mutex);
  sem_post(queue->*num_items_avail);
}

void blocking_queue_dequeue(blocking_queue_t *queue, int *value){
  sem_wait(queue->*num_items_avail);   
  pthread_mutex_lock(queue->*modify_mutex);
  queue_element_t *to_return = queue->head;
  queue->head = queue->head->next;
  pthread_mutex_unlock(queue->*modify_mutex);
  *value = to_return->value;
  free(to_return);
}

void get_size(blocking_queue_t *queue, int *value){
  sem_getvalue(queue->*num_items_avail, value);
}
