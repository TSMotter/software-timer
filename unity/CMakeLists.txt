# Creates a binary target
add_library(unity STATIC ${CMAKE_CURRENT_LIST_DIR}/src/unity.c 
                         ${CMAKE_CURRENT_LIST_DIR}/src/unity.h
                         ${CMAKE_CURRENT_LIST_DIR}/src/unity_internals)