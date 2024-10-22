file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_executable(RoverRun ${SOURCES})
target_include_directories(RoverRun PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(RoverRun PRIVATE Base)
target_link_libraries(RoverRun PRIVATE Debug)