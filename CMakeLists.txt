cmake_minimum_required(VERSION 2.8)
project(cimunit C)

if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -std=c99")
endif( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )

# Add definitions for platform specific code
add_definitions("-DPLATFORM_${CMAKE_SYSTEM_NAME}")

enable_testing()
FIND_PACKAGE(Threads)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(unitTests)

find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
  ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)