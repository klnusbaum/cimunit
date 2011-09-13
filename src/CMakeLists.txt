set(CIMUNIT_SRC
  cimunit.c
  cimunit_event.c
  cimunit_mutex.c
  cimunit_schedule.c
  cimunit_tester.c
  cimunit_thread.c
)
   
set(CIMUNIT_HDRS
  cimunit.h
  cimunit_event.h
  cimunit_mutex.h
  cimunit_schedule.h
  cimunit_tester.h
  cimunit_thread.h
)

add_library(cimunit ${CIMUNIT_SRC} ${CIMUNIT_HDRS})
target_link_libraries(cimunit ${CMAKE_THREAD_LIBS_INIT})

add_executable(sample sample.c)
target_link_libraries(sample cimunit)

