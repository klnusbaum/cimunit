include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(get_event_test get_event_test.c)
target_link_libraries(get_event_test cimunit)
