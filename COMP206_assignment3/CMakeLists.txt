cmake_minimum_required (VERSION 2.8.9)
project (Q3COMP206)

add_library(swapLib SHARED encryption.c)

add_executable(Q3COMP206 q3_encrypted_chat.c)
target_link_libraries(Q3COMP206 swapLib)

# The version number.
#set (Q3COMP206_VERSION_MAJOR 1)
#set (Q3COMP206_VERSION_MINOR 0)
 
# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/encryption.h"
#  "${PROJECT_BINARY_DIR}/encryption.h"
#  )
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
#include_directories("${PROJECT_BINARY_DIR}")
 
# add the executable
#add_executable(Tutorial q3_encrypted_chat.c)

