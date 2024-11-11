# Creates a binary target
add_executable(main main.c)

# use, i.e. don't skip the full RPATH for the build tree
set_target_properties(main PROPERTIES SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set_target_properties(main PROPERTIES BUILD_WITH_INSTALL_RPATH FALSE)

# the RPATH to be used when installing
set_target_properties(main PROPERTIES INSTALL_RPATH "")

# don't add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set_target_properties(main PROPERTIES INSTALL_RPATH_USE_LINK_PATH FALSE)

# Includes directories and links targets into target
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(main PRIVATE gm_timer)

install(TARGETS main ${CMAKE_INSTALL_BINDIR})