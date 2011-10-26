find_package(FLEX)
FLEX_TARGET(scanner create_events.l  ${CMAKE_CURRENT_BINARY_DIR}/create_events_lexer.c)

find_package(BISON)
BISON_TARGET(grammar create_events.y ${CMAKE_CURRENT_BINARY_DIR}/create_events_grammar.c
             COMPILER_FLAGS "-d")
ADD_FLEX_BISON_DEPENDENCY(scanner grammar)

set(CIMUNIT_SRC
  cimunit.c
  cimunit_barrier_unix.c
  cimunit_event.c
  cimunit_event_list.c
  cimunit_mutex.c
  cimunit_schedule.c
  cimunit_tester.c
  cimunit_thread.c
  cimunit_event_table.c
  ${FLEX_scanner_OUTPUTS}
  ${BISON_grammar_OUTPUTS}
)

add_library(cimunit ${CIMUNIT_SRC})
target_link_libraries(cimunit ${CMAKE_THREAD_LIBS_INIT})

add_executable(sample sample.c)
target_link_libraries(sample cimunit)
