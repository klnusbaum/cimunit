/**
 * \file concurrent_queue.h
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
#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H
#include <pthread.h>

/// Structure defining an element within a concurrent queue.
typedef struct queue_element{
  /// The actual int value that's queued.
  int value;
  
  /// A pointer pointing to the next element in the queue.
  struct queue_element *next;
} queue_element_t;


/// Structure defining a concurrent queue
typedef struct{

  /// A pointer that points to the head of the queue. NULL if there are 
  /// no items in the queue.
  queue_element_t *head;

  /// A pointer that points to the tail of the queueu. NULL if there are
  /// no items in the queue.
  queue_element_t *tail;

  /// A mutex that protects critical sections in queue related code that 
  /// modifies the queue.
  pthread_mutex_t modify_mutex;

  /// The number of elements in the queue.
  size_t size;
} concurrent_queue_t;

void queue_element_init(queue_element_t *element, int value);
  
void concurrent_queue_init(concurrent_queue_t *queue);
void concurrent_queue_destroy(concurrent_queue_t *queue);
void concurrent_queue_enqueue(concurrent_queue_t *queue, int value);
int concurrent_queue_dequeue(concurrent_queue_t *queue, int *value);
void concurrent_queue_size(concurrent_queue_t *queue, size_t *value);


#endif //CONCURRENT_QUEUE_H
