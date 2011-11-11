set(QUEUE_EXAMPLE_SRC
  concurrent_queue.c
  test_example.c
) 

add_executable(queue_test ${QUEUE_EXAMPLE_SRC})
target_link_libraries(queue_test cimunit ${CMAKE_THREAD_LIBS_INIT})
