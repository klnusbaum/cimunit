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
#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H
#include <pthread.h>
#include <sys/semaphore.h>

typedef struct queue_element{
  int value;
  struct *queue_element next;
} queue_element_t;


typedef struct{
  queue_element_t *head;
  queue_element_t *tail;
  sem_t num_items_avail;
  pthread_mutex_t modify_mutex;
} blocking_queue_t;

void queue_element_init(queue_element_t *element, int value);
  
void blocking_queue_init(blocking_queue_t *queue);
void blocking_queue_destroy(blocking_queue_t *queue);
void blocking_queue_enqueue(blocking_queue_t *queue, int value);
void blocking_queue_dequeue(blocking_queue_t *queue, int *value);
void get_size(blocking_queue_t *queue, int *value);


#endif //BLOCKING_QUEUE_H
