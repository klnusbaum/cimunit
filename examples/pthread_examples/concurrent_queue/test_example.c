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

/// This is a structure we will use to pass arguements to our thread 
/// functions
typedef struct{
  cimunit_schedule_t *schedule;
  concurrent_queue_t *queue;
  int dequeued_value;
  int dequeue_return_val;
} thread_args_t;


///More on these later...
void *consumer_function(void *args);
void *producer_function(void *args);

int main(int argc, char *argv[]){
  /**
   * Welcome to CIMUnit, the multithreading testing framework. We're going
   * to do a quick simple example for you here to help get you started.
   * Nothing to complicated. Just something to show you how to use some of 
   * the basic features of CIMUnit.
   */

  /**
   * In this example we're going to be testing a basic concurrent queue 
   * structure we've put together. This data strcuture is basic queue that allow
   * for multiple threads to queue and dequeue elements from it in a safe 
   * manner. There's an important feature of our queue to note, if one thread
   * attempts to dequeue an element from the queue and the queue is empty, 
   * the dequeue funtion will return an error code. Don't worry about this
   * too much now, but it's a little detail that's going to come up later.
   * If you want more about the implementation details of this concurrent queue,
   * feel free to take a look at the concurrent_queue.(h|c) files. 
   */

  /**
   * CIMUnit is flexible and can be integrated into your testing framework of
   * choice. For this example thought, we're just going to use a simple error
   * variable to keep track of any testing failures.
   */
  int error = 0;

  /** 
   * Here we're going to declare and initialize the queue we want to use.
   */
  concurrent_queue_t queue;
  concurrent_queue_init(&queue);
   

  /**
   * Our test is going to consist of two threads. One, the producuer, will be
   * adding an element to the queue. The other, the consumer, will be 
   * dequeuing an item from the queue. For our first test, we just want to
   * ensure that everything works out nicely as long as our producer thread
   * enqueues a value before our consumer thread does a dequeue. In CIMUnit,
   * we can enforce thread schedules using a schedule data strucuture. When
   * initializing this data structure, we pass a string representing our
   * desired schedule. In this case, we want to ensure that we start our 
   * dequeue only after we end our enqueue. All of this is accomplished using
   * the simple line of code below.
   */
  cimunit_schedule_t *schedule = cimunit_schedule_parse(
    "endEnqueue1->startDequeue1");

  /**
   * CIMUnit schedules are comprised mostly of what are called "events". 
   * CIMUnit schedules enforce particular threading schedules by ensuring that
   * a certain sequence of events occur. The schedule 
   * "end_equeue1->start_dequeue1" says that the "end_enqueue1" event must
   * occur before the "start_dequeue1" event occurs.
   *
   * Now, you may be saying to yourself, "Hey bub, how does the schedule know
   * when my enqueue has ended and my dequeue has started?" Well take a quick
   * look down at our producer and consumer funcitons. You'll notice that 
   * we've passed our schedule object down into them and we "fire" off events
   * let to let the schedule know certain events have occurred.
   */


  /** 
   * Here we're just packing up the arguments that we want to send to each
   * of our thread functions. Note that we're passing the schedule to the
   * funcitons. As a generall rule of thumb, you're pretty much always going
   * to want to be passing a pointer to the schedule to your thread functions.
   */
  thread_args_t args;
  args.queue = &queue;
  args.schedule = schedule;
  args.dequeued_value = 0;
  args.dequeue_return_val = 0;

  /**
   * Here we create and launch our threads using standard pthreads functions.
   */
  pthread_t producer_thread;
  pthread_t consumer_thread;
  pthread_create(&producer_thread, NULL, producer_function, (void*)(&args));
  pthread_create(&consumer_thread, NULL, consumer_function, (void*)(&args));

  /**
   * Here we ensure that our threads have terminated using standard pthreads
   * functions.
   */
  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);

  /**
   * Ok, our thread functions ran. What just happened. Well if you take 
   * another peek down at the thread functions you'll see that if our
   * schedule was enforces properly, the enqueue function should have
   * first enqueued a "5" and then our consumer function should have dequeued
   * the "5". If our concurrent queue structure functioned the way it should
   * have, we should no have args.revale set to 5, the dequeue_return_val set
   * set to 0, and the queue size be equal to one. This is what we check below.
   * When you run this executable, hopefully your get the message that the
   * test passed!
   */
  size_t queue_size;
  concurrent_queue_size(&queue, &queue_size);
  if(args.dequeued_value == 5 &&
     args.dequeue_return_val == 0 &&
     queue_size == 0)
  {
    printf("Test 1 passed :)\n");
  }
  else{
    fprintf(stderr, "Test 1 failed!\n");
    fprintf(stderr, "Dequeued value was: %d\n", args.dequeued_value);
    fprintf(stderr, "Dequeue return value was: %d\n", args.dequeue_return_val);
    fprintf(stderr, "Size was: %zu\n", queue_size);
    error +=1;
  }

  /**
   * Before finishing up this test, we destroy the schedule and the queue.
   */
  cimunit_schedule_destroy(schedule);
  concurrent_queue_destroy(&queue);


  /**
   * One of the cool things about CIMUnit is that you can test the same set
   * of functions with a differnet thread schedule. The idea being that you
   * shouldn't have to write essentially identical functions just to test 
   * different thread schedules. Let's try testing some different functionaliy
   * this time around. Remember how I told you that if you try to dequeue 
   * something from an empty queue, you're not going to qet anything out and the
   * dequeue function should return an error code? We'll let's see if we can
   * verify this behavior. Let's create a new schedule were we finish our
   * dequeue attempt before the enqueue starts.
   */
  schedule = cimunit_schedule_parse("endDequeue1->startEnqueue1");
 
  /**
   * Once again, we'll initilize our queue and the values for the arguements
   * we're going to pass to each of our threading funcitons.
   */
  concurrent_queue_init(&queue);
  args.dequeued_value=0;
  args.dequeue_return_val = 0;
  args.schedule = schedule;
  
  /**
   * We then create, launch and join our threads using the standard pthread
   * funcitons just like before.
   */
  pthread_create(&producer_thread, NULL, producer_function, (void*)(&args));
  pthread_create(&consumer_thread, NULL, consumer_function, (void*)(&args));
  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);


  /**
   * Alright, so what should have happened? If our schedule was enforced and
   * the concurrent queue functioned as specified, we should have attempted
   * to dequeue before anything was ever equeued in the queue. This should
   * result in our dequeued value not chaning from 0, the return value from
   * the dequeue funciton not being 0 (it's an error code), and the queue
   * size now being one because we did after all actually enqueue and element.
   * The code below verifies this and if you run the test you should see 
   * that it passed.
   */

  concurrent_queue_size(&queue, &queue_size);
  if(args.dequeued_value == 0 && 
     args.dequeue_return_val != 0 &&
     queue_size == 1)
  {
    printf("Test 2 passed :)\n");
  }
  else{
    fprintf(stderr, "Test 2 failed!\n");
    fprintf(stderr, "Dequeued value was: %d\n", args.dequeued_value);
    fprintf(stderr, "Dequeue return value was: %d\n", args.dequeue_return_val);
    fprintf(stderr, "Size was: %zu\n", queue_size);
    error +=1;
  }

  /**
   * Once again, we now destroy the schedule and queue objects.
   */
  cimunit_schedule_destroy(schedule);
  concurrent_queue_destroy(&queue);
  
  /**
   * That's about it. If there were any errors (which there shouldn't have been)
   * our return value would be non-zero. Once agin, CIMUnit is flexible
   * enough that you can use your testing framework of choice to verify test
   * results. This has been just a basic example of how to use CIMUnit.
   * If you're interested in learning more, checkout some of our more 
   * complicated examples.
   */
  return error;
}

/// Consumer thread funciton
void *consumer_function(void *args){
  thread_args_t *thread_args = (thread_args_t*)args;
  concurrent_queue_t *queue = thread_args->queue;
  cimunit_schedule_t *schedule = thread_args->schedule;

  /**
   * Inform the schedule that we've begun attempting to dequeue an element.
   */
  cimunit_schedule_fire(schedule, "startDequeue1");
  thread_args->dequeue_return_val = 
    concurrent_queue_dequeue(queue, &(thread_args->dequeued_value));
  /**
   * Inform the schedule that we've finished attempting to dequeue an element.
   */
  cimunit_schedule_fire(schedule, "endDequeue1");
}

/// Producer thread funciton
void *producer_function(void *args){
  thread_args_t *thread_args = (thread_args_t*)args;
  concurrent_queue_t *queue = thread_args->queue;
  cimunit_schedule_t *schedule = thread_args->schedule;
  
  /**
   * Inform the schedule that we've begun enquue an element.
   */
  cimunit_schedule_fire(schedule, "startEnqueue1");
  concurrent_queue_enqueue(queue, 5);
  /**
   * Inform the schedule that we've finished enquueing an element.
   */
  cimunit_schedule_fire(schedule, "endEnqueue1");
}

