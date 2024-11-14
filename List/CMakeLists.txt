cmake_minimum_required(VERSION 3.22)
project(List C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(List STATIC ${SOURCES})

target_include_directories(List PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (COVERAGE AND NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(List PRIVATE --coverage -fprofile-arcs -ftest-coverage)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests AND ${TESTS})
    add_subdirectory(tests)
endif()