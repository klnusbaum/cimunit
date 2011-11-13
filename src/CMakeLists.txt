find_package(FLEX 2.5.33 REQUIRED flex)
find_package(BISON 2.4.1 REQUIRED bison)

FLEX_TARGET(create_events_lexer create_events.l
            ${CMAKE_CURRENT_BINARY_DIR}/create_events_lexer.c)
BISON_TARGET(create_events_grammar create_events.y
             ${CMAKE_CURRENT_BINARY_DIR}/create_events_grammar.c
             COMPILER_FLAGS "-d")
ADD_FLEX_BISON_DEPENDENCY(create_events_lexer create_events_grammar)


FLEX_TARGET(parse_events_lexer parse_events.l
            ${CMAKE_CURRENT_BINARY_DIR}/parse_events_lexer.c)
BISON_TARGET(parse_events_grammar parse_events.y
             ${CMAKE_CURRENT_BINARY_DIR}/parse_events_grammar.c
             COMPILER_FLAGS "-d")
ADD_FLEX_BISON_DEPENDENCY(parse_events_lexer parse_events_grammar)


set(CIMUNIT_SRC
  cimunit.c
  cimunit_barrier_pthread.c
  cimunit_event.c
  cimunit_event_list.c
  cimunit_mutex_pthread.c
  cimunit_schedule.c
  cimunit_thread_pthread.c
  cimunit_event_table.c
  cimunit_thread_table.c
  ${FLEX_create_events_lexer_OUTPUTS}
  ${BISON_create_events_grammar_OUTPUTS}
  ${FLEX_parse_events_lexer_OUTPUTS}
  ${BISON_parse_events_grammar_OUTPUTS}
)

add_library(cimunit ${CIMUNIT_SRC})
target_link_libraries(cimunit ${CMAKE_THREAD_LIBS_INIT})

