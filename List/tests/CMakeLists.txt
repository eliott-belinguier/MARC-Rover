find_package(Criterion REQUIRED)

file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_executable(test_list ${TEST_SOURCES})

target_link_libraries(test_list PRIVATE List criterion)
target_include_directories(test_list PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_custom_target(tests_run
        DEPENDS test_list
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
)

if (COVERAGE)
    find_program(GCOVR_EXECUTABLE gcovr REQUIRED)
    if(NOT GCOVR_EXECUTABLE)
        message(FATAL_ERROR "gcovr binary not found!")
    endif()
    target_link_libraries(test_list PRIVATE gcov)
    add_custom_target(coverage
            DEPENDS tests_run
            COMMAND ${GCOVR_EXECUTABLE} --branches --exclude ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/tests --root ${CMAKE_SOURCE_DIR}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage/${PROJECT_NAME}
            COMMAND ${GCOVR_EXECUTABLE} --branches --exclude ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/tests --root ${CMAKE_SOURCE_DIR} --html-details -o ${CMAKE_BINARY_DIR}/coverage/${PROJECT_NAME}/index.html ${CMAKE_SOURCE_DIR}
            COMMENT "Running tests and generating coverage report in HTML format."
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()


add_test(NAME test_list COMMAND test_list)