# Creates a binary target
add_executable(tests test_gm_timer.c)

# Includes directories and links targets into target
target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR}/external/unity)
target_link_libraries(tests PRIVATE gm_timer)
target_link_libraries(tests PRIVATE unity)

# Adds test
add_test(my_tests main)