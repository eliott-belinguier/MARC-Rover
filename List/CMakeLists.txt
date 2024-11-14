cmake_minimum_required(VERSION 3.22)
project(List C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(List STATIC ${SOURCES})

target_include_directories(List PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (TESTS)
    target_compile_options(List PRIVATE -ggdb3)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
        add_subdirectory(tests)
    endif()
endif()

if (COVERAGE)
    find_program(GCOVR_EXECUTABLE gcovr REQUIRED)
    if(NOT GCOVR_EXECUTABLE)
        message(FATAL_ERROR "gcovr binary not found!")
    endif()
    target_link_libraries(List PRIVATE gcov)
    target_compile_options(List PRIVATE --coverage -fprofile-arcs -ftest-coverage)
endif()