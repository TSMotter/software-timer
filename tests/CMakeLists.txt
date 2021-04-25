# Creates a binary target
add_executable(test_gm_timer test_gm_timer.c)

# Includes directories and links targets into target
target_include_directories(test_gm_timer PUBLIC ${CMAKE_SOURCE_DIR}/drv)
target_include_directories(test_gm_timer PUBLIC ${CMAKE_SOURCE_DIR}/unity/src)
target_link_libraries(test_gm_timer PRIVATE gm_timer)
target_link_libraries(test_gm_timer PRIVATE unity)

# Adds test
add_test(my_tests test_gm_timer)