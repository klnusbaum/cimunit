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

#include "cimunit.h"
#include "concurrent_queue.h"
#include <assert.h>
#include <stdio.h>

typedef struct{
  cimunit_schedule_t *schedule;
  concurrent_queue_t *queue;
  int retval;
  int dequeue_return_val;
} thread_args_t;

void *consumer_function(void *args){
  thread_args_t *thread_args = (thread_args_t*)args;
  concurrent_queue_t *queue = thread_args->queue;
  cimunit_schedule_t *schedule = thread_args->schedule;

  cimunit_schedule_fire(schedule, "start_dequeue1");
  thread_args->dequeue_return_val = 
    concurrent_queue_dequeue(queue, &(thread_args->retval));
  cimunit_schedule_fire(schedule, "end_dequeue1");
}

void *producer_function(void *args){
  thread_args_t *thread_args = (thread_args_t*)args;
  concurrent_queue_t *queue = thread_args->queue;
  cimunit_schedule_t *schedule = thread_args->schedule;
  
  cimunit_schedule_fire(schedule, "start_enqueue1");
  concurrent_queue_enqueue(queue, 5);
  cimunit_schedule_fire(schedule, "end_enqueue1");
}

int main(int argc, char *argv[]){
  int error = 0;
  cimunit_schedule_t *schedule = cimunit_schedule_parse(
    "end_enqueue1->start_dequeue1");
  concurrent_queue_t queue;
  concurrent_queue_init(&queue);
   
  thread_args_t args;
  args.queue = &queue;
  args.schedule = schedule;
  args.retval = 0;
  args.dequeue_return_val = 0;

  pthread_t producer_thread;
  pthread_t consumer_thread;
  pthread_create(&producer_thread, NULL, producer_function, (void*)(&args));
  pthread_create(&consumer_thread, NULL, consumer_function, (void*)(&args));

  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);

  size_t queue_size;

  concurrent_queue_size(&queue, &queue_size);
  if(args.retval != 5 && args.dequeue_return_val != 0 && queue_size == 0){
    fprintf(stderr, "Test 1 failed!\n");
    error +=1;
  }
  else{
    printf("Test 1 passed :)\n");
  }

  cimunit_schedule_destroy(schedule);
  concurrent_queue_destroy(&queue);


  schedule = cimunit_schedule_parse("end_dequeue1->start_enqueue1");
  concurrent_queue_init(&queue);
  args.retval=0;
  args.dequeue_return_val = 0;
  args.schedule = schedule;
  
  pthread_create(&producer_thread, NULL, producer_function, (void*)(&args));
  pthread_create(&consumer_thread, NULL, consumer_function, (void*)(&args));

  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);
  concurrent_queue_size(&queue, &queue_size);


  if(args.retval != 0 && args.dequeue_return_val != 1 && queue_size ==1){
    fprintf(stderr, "Test 2 failed!\n");
    error +=1;
  }
  else{
    printf("Test 2 passed :)\n");
  }

  cimunit_schedule_destroy(schedule);
  concurrent_queue_destroy(&queue);
  
  return error;


}
