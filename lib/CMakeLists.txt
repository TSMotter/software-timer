# Creates a binary target - in this case, a shared library
add_library (gm_timer SHARED gm_timer.c gm_timer.h)

set_target_properties(gm_timer PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(gm_timer PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(gm_timer PROPERTIES PUBLIC_HEADER gm_timer.h)

install(TARGETS gm_timer ${CMAKE_INSTALL_LIBDIR})