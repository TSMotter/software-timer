# Creates a binary target - in this case, a shared library
add_library (gm_timer SHARED gm_timer.c gm_timer.h)

set_target_properties(gm_timer PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(gm_timer PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

install(TARGETS gm_timer ${CMAKE_INSTALL_LIBDIR})