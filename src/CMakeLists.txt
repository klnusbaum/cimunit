set(CIMUNIT_SRC
  cimunit.c
  cimunit_barrier_unix.c
  cimunit_event.c
  cimunit_mutex.c
  cimunit_schedule.c
  cimunit_tester.c
  cimunit_thread.c
)
   
add_library(cimunit ${CIMUNIT_SRC})
target_link_libraries(cimunit ${CMAKE_THREAD_LIBS_INIT})

add_executable(sample sample.c)
target_link_libraries(sample cimunit)