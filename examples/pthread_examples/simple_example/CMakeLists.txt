set(QUEUE_EXAMPLE_SRC
  ../concurrent_queue.c
  test_example.c
) 

add_executable(simple_test ${QUEUE_EXAMPLE_SRC})
target_link_libraries(simple_test cimunit ${CMAKE_THREAD_LIBS_INIT})
