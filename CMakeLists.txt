cmake_minimum_required(VERSION 3.28)
project(RoverRun C)

set(CMAKE_C_STANDARD 99)

option(DEBUG "Enable debug mode" OFF)
option(TESTS "Compile and Execute unit tests" OFF)
option(COVERAGE "Show coverage of tests" OFF)

if(DEBUG)
    message(WARNING "Debug mode enabled.")
    add_definitions(-DDEBUG=1)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb3 -O0")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
endif()

add_subdirectory(Debug)
add_subdirectory(Core)
add_subdirectory(RoverRun)