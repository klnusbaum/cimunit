add_executable(simple_test pthread_example.c)
target_link_libraries(simple_test cimunit ${CMAKE_THREAD_LIBS_INIT})
