include(FindCUnit)
find_package(CUnit REQUIRED cunit)
find_package(Curses REQUIRED NCurses)
set(CIMUNIT_UNIT_TESTS
  testMain.c
  test_cimunit_event.c
  test_cimunit_event_list.c
  test_cimunit_schedule.c
  test_cimunit.c
)
   
set(CIMUNIT_HDRS_UNIT_TESTS
)

#This is machine dependent. We should let user specify where there CUnit install is.
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -I/opt/local/include/CUnit -L/opt/local/lib")
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CUNIT_INCLUDE_DIRS})

add_executable(unitTests ${CIMUNIT_UNIT_TESTS})
add_executable(barrierTest barrier_test.c)
target_link_libraries(unitTests cimunit ${CUNIT_LIBRARIES} ${CURSES_LIBRARIES})
target_link_libraries(barrierTest cimunit)

add_test(barrierTest, ${CMAKE_CURRENT_BINARY_DIR}/barrierTest)
add_test(unitTests, ${CMAKE_CURRENT_BINARY_DIR}/unitTests)

add_executable(scantest scantest.c)
target_link_libraries(scantest cimunit)
