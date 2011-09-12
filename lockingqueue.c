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

#include <pthread.h>
#include <stdlib.h>

typedef struct{
  void *data;
  QueueElement *next;
} QueueElement;

typedef struct{
  pthread_mutex_t queueLock;
  QueueElement *head;
  QueueElement *tail;
} LockingQueue;

int init_queue(LockingQueue &queue){
  pthread_attr_init(&(queue.queueLock));
}

int enqueue(LockingQueue &queue, QueueElement *toEnqueue){
  pthread_mutex_loc(&(queue.queueLock));
  if(queue.head == NULL){
    queue.head = toEnqueue;
    queue.tail = toEnqueue;
  }
  else{
    queue.tail.next = toEnqueue;
    queue.tail = toEnqueue;
  }  
  pthread_mutex_unlock(&(queue.queueLock));
}

int dequeue(LockingQueue &queue, QueueElement& toDequeue){
  pthread_mutex_loc(&(queue.queueLock));
  if(queue.head == NULL){
    toDequeue = NULL;
  }
  else{
    toDequeue = queue.head;
    queue.head = head->next;
  }
  pthread_mutex_unlock(&(queue.queueLock));
}

int destroy_queue(LockingQueue &queue){
  pthread_mutex_destroy(&(queue.queueLock));
}
