# Creates a binary target
add_executable(main main.c)

# Includes directories and links targets into target
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/drv)
target_link_libraries(main PRIVATE gm_timer)