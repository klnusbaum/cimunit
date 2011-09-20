cmake_minimum_required(VERSION 2.8)
project(cimunit C Java)
message(STATUS ${CMAKE_SYSTEM_NAME})

# Define PLATFORM_Darwin, PLATFORM_Linux, etc... to support platform specific
# customizations of CIMunit
set(CMAKE_C_FLAGS "-std=c99 -D PLATFORM_${CMAKE_SYSTEM_NAME}")

ENABLE_TESTING()
find_package(Threads)
add_subdirectory(src)
add_subdirectory(tests)
