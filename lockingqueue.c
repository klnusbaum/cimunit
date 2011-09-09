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
