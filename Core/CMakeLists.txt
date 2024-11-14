file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/MARC/src/*.c")

add_library(Core STATIC ${SOURCES})

IF (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(Core PRIVATE -Wno-unused-result)
ENDIF()

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/MARC/include)