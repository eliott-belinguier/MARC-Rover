cmake_minimum_required(VERSION 3.22)
project(RoverRun C)

set(CMAKE_C_STANDARD 99)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

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

if (${TESTS})
    enable_testing()
    set(CMAKE_CTEST_ARGUMENTS "--output-on-failure")
endif()

add_subdirectory(Debug)
add_subdirectory(List)
add_subdirectory(Core)
add_subdirectory(RoverRun)

get_property(TEST_EXECUTABLES GLOBAL PROPERTY TEST_EXECUTABLES)

add_custom_target(build_tests
        DEPENDS ${TEST_EXECUTABLES}
)

add_custom_target(tests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS build_tests
)