include(FindCUnit)

find_package(CUnit REQUIRED cunit)
find_package(Curses REQUIRED NCurses)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CUNIT_INCLUDE_DIRS})

add_library(cimunit_test_library testMain.c)


macro (CREATE_UNIT_TEST  testname filename )
  add_executable( ${testname} ${filename} testMain.c)
  target_link_libraries( ${testname} cimunit cimunit_test_library ${CUNIT_LIBRARIES} ${CURSES_LIBRARIES})
  add_test( ${testname}  ${CMAKE_CURRENT_BINARY_DIR}/${testname} "-v")
endmacro(CREATE_UNIT_TEST)

CREATE_UNIT_TEST(eventTests test_cimunit_event.c)
CREATE_UNIT_TEST(eventListTests test_cimunit_event_list.c)
CREATE_UNIT_TEST(scheudleTests test_cimunit_schedule.c)
CREATE_UNIT_TEST(cimunitTests test_cimunit.c)
CREATE_UNIT_TEST(testParseEvents test_parse_events.c)
CREATE_UNIT_TEST(eventTableEntryTests test_cimunit_event_table_entry.c)
CREATE_UNIT_TEST(eventTableTests test_cimunit_event_table.c)
CREATE_UNIT_TEST(scanTest test_scantest.c)
CREATE_UNIT_TEST(barrierTest test_cimunit_barrier.c)


