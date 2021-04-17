cmake_minimum_required (VERSION 3.14)
project (SofTim)

# Variable TARGET_GROUP should be passed as an argument when callin the cmake
set(TARGET_GROUP production CACHE STRING "What Should I Build?")

# Should be present in all builds
add_subdirectory (drv) 

if(TARGET_GROUP STREQUAL release)
  add_subdirectory (src)
elseif(TARGET_GROUP STREQUAL test)
  include(CTest)
  add_subdirectory(unity)
  add_subdirectory(tests)
  enable_testing()
else()
  message(FATAL_ERROR "I don't know the TARGET_GROUP you gave me!")
endif()
