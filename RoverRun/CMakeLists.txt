file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_executable(RoverRun ${SOURCES})
target_include_directories(RoverRun PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(RoverRun PRIVATE Core)
target_link_libraries(RoverRun PRIVATE Debug)
target_link_libraries(RoverRun PRIVATE List)

if (TESTS)
    target_compile_options(RoverRun PRIVATE -ggdb3)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
        add_subdirectory(tests)
    endif()
endif()

if (COVERAGE)
    find_program(GCOVR_EXECUTABLE gcovr REQUIRED)
    if(NOT GCOVR_EXECUTABLE)
        message(FATAL_ERROR "gcovr binary not found!")
    endif()
    target_link_libraries(RoverRun PRIVATE gcov)
    target_compile_options(RoverRun PRIVATE --coverage -fprofile-arcs -ftest-coverage)
endif()