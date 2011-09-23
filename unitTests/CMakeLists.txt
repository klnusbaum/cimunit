set(CIMUNIT_UNIT_TESTS
  testMain.c
  test_cimunit_event.c
)
   
set(CIMUNIT_HDRS_UNIT_TESTS
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -I/opt/local/include/CUnit -L/opt/local/lib")
include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(unitTest ${CIMUNIT_UNIT_TESTS})
target_link_libraries(unitTest cimunit cunit ncurses)
add_custom_target(runTests
                  unitTest
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  COMMENT "Running Unit Tests" VERBATIM
)
