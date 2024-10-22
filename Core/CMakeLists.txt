file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/MARC/*.c")

add_library(Base STATIC ${SOURCES})

IF (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(Base PRIVATE -Wno-unused-result)
ENDIF()

target_include_directories(Base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/MARC)