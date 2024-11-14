file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/MARC/src/*.c")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/MARC/src/main.c")

add_library(Core STATIC ${SOURCES})

IF (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(Core PRIVATE -Wno-unused-result)
ENDIF()

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/MARC/include)

if (TESTS)
    target_compile_options(Core PRIVATE -ggdb3)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
        add_subdirectory(tests)
    endif()
endif()

if (COVERAGE)
    find_program(GCOVR_EXECUTABLE gcovr REQUIRED)
    if(NOT GCOVR_EXECUTABLE)
        message(FATAL_ERROR "gcovr binary not found!")
    endif()
    target_link_libraries(Core PRIVATE gcov)
    target_compile_options(Core PRIVATE --coverage -fprofile-arcs -ftest-coverage)
endif()