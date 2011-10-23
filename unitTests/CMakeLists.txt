set(CIMUNIT_UNIT_TESTS
  testMain.c
  test_cimunit_event.c
  test_cimunit_event_list.c
  test_cimunit_schedule.c
)
   
set(CIMUNIT_HDRS_UNIT_TESTS
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -I/opt/local/include/CUnit -L/opt/local/lib")
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(unitTests ${CIMUNIT_UNIT_TESTS})
add_executable(barrierTest barrier_test.c)
target_link_libraries(unitTests cimunit cunit ncurses)
target_link_libraries(barrierTest cimunit)

add_test(barrierTest, ${CMAKE_CURRENT_BINARY_DIR}/barrierTest)
add_test(unitTests, ${CMAKE_CURRENT_BINARY_DIR}/unitTests)
