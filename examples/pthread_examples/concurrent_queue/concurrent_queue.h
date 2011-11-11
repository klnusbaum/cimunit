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

/// Initalizes an element for a queue.
///
/// \param element - The queue element to be initialized
/// \param element - The value which the element shall hold.
void queue_element_init(queue_element_t *element, int value);
  
/// Initializes a concurrent queue.
///
/// \param queue - The queue to be initialized
void concurrent_queue_init(concurrent_queue_t *queue);

/// Frees all alocated resources for concurrent queue.
///
/// \param queue - The queue to be destroyed.
void concurrent_queue_destroy(concurrent_queue_t *queue);

/// Enqueues a value in the given concurrent queue.
///
/// \param queue - The queue into which the value shall be enqueue.
/// \param value - The value to enqueue.
void concurrent_queue_enqueue(concurrent_queue_t *queue, int value);

/// Dequeus the next element from the queue.
///
/// \param queue - The queue from which a value should be dequeued.
/// \param value - A pointer into which the value of the dequeued element is
///  stored.
/// \return - 0 if an element was successfully dequeued. If the queue
///  was empty and therefore nothing was dequeued, this funciton returns 1.
int concurrent_queue_dequeue(concurrent_queue_t *queue, int *value);

/// Gets the size of a queue.
///
/// \param queue - The queue whose size is desired.
/// \param value - A pointer into which the size of the queue will be stored.
void concurrent_queue_size(concurrent_queue_t *queue, size_t *size);


#endif //CONCURRENT_QUEUE_H
