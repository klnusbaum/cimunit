#include "cimunit.h"

#include <stddef.h>

#include "cimunit_event_list.h"
#include "cimunit_event_table.h"
#include "cimunit_schedule.h"

struct cimunit_schedule *g_cimunit_default_schedule = NULL;


bool cimunit_fire(struct cimunit_schedule *schedule, char *eventName)
{
    // Locate the event in the schedule and fire it.
    cimunit_event_t *event = cimunit_event_list_find(schedule->event_list, eventName);
    if (event) {
        cimunit_add_event_to_table(&schedule->fired_event_list, event, NULL);
        cimunit_event_fire(event);
        if (event->is_action) {
            while (!cimunit_parse_schedule_runtime(schedule, eventName)) {
                cimunit_event_lock_and_wait(event);
            }
        }
    } else {
        return false;
    }
    
    return true;
}


#include "cimunit_thread.h"


int cimunit_run_test(void *(*test_func)(void *), cimunit_schedule_t *sc){
  cimunit_thread_id_t i;
  cimunit_thread_t *threads = 
    (cimunit_thread_t*)malloc(sizeof(cimunit_thread_t)*(sc->numThreads));
  cimunit_test_args_t *args = 
    (cimunit_test_args_t*)malloc(sizeof(cimunit_test_args_t)*(sc->numThreads));
  
  for(i=0;i<sc->numThreads;++i){
    args[i].schedule = sc;
    args[i].thread = i;
    cimunit_thread_create(&(threads[i]), NULL, test_func, (void*)(&(args[i]))); 
  }

  for(i=0;i<sc->numThreads; ++i){
    //TODO, instead of null we'll actually wanna look at the return value.
    cimunit_thread_join(threads[i], NULL);
  }
  free(threads);
  free(args);
}


int cimunit_run_tests(cimunit_tester_t *tester){
  cimunit_test_instance_t *nextTest = tester->headTest;
  while(nextTest != NULL){
    cimunit_run_test(nextTest->test_func, nextTest->sc);
    nextTest = nextTest->next;
  }
  cimunit_test_instance_t *to_dealloc;
  nextTest = tester->headTest;
  while(nextTest != NULL){
    to_dealloc = nextTest;
    nextTest = nextTest->next;
    free(to_dealloc);
  }

}

