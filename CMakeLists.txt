cmake_minimum_required(VERSION 2.8)
project(cimunit C)

if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -std=c99")
endif( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )

# Add definitions for platform specific code
add_definitions("-DPLATFORM_${CMAKE_SYSTEM_NAME}")

ENABLE_TESTING()
FIND_PACKAGE(Threads)
add_subdirectory(src)
add_subdirectory(tests)
