cmake_minimum_required (VERSION 3.14)
project (software-timer VERSION 0.1 DESCRIPTION "Simple Software Timer Module")

# Variable TARGET_GROUP should be passed as an argument when callin the cmake
set(TARGET_GROUP production CACHE STRING "What Should I Build?")

# Should be present in all builds
add_subdirectory (lib) 

if(TARGET_GROUP STREQUAL example)
  add_subdirectory (example)
elseif(TARGET_GROUP STREQUAL tests)
  include(CTest)
  add_subdirectory(external)
  add_subdirectory(tests)
  enable_testing()
elseif(TARGET_GROUP STREQUAL lib)
  message("-- Building only the driver itself as a shared library")
else()
  message(FATAL_ERROR "I don't know the TARGET_GROUP you gave me!")
endif()
