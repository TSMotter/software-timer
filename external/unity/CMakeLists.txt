# Creates a binary target
add_library(unity STATIC ${CMAKE_CURRENT_LIST_DIR}/unity.c 
                         ${CMAKE_CURRENT_LIST_DIR}/unity.h
                         ${CMAKE_CURRENT_LIST_DIR}/unity_internals.h)