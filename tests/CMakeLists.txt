# Creates a binary target
add_executable(main test_gm_timer.c)

# Includes directories and links targets into target
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/drv)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/external/unity)
target_link_libraries(main PRIVATE gm_timer)
target_link_libraries(main PRIVATE unity)

# Adds test
add_test(my_tests main)