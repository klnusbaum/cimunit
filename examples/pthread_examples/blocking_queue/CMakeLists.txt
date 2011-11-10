set(BLOCK_QUEUE_SRC
  blocking_queue.c
) 

add_target(block_test ${BLOCK_QUEUE_SRC})
target_link_libraries(block_test cimunit ${CMAKE_THREAD_LIBS_INIT})
