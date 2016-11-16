cmake_minimum_required (VERSION 2.8.9)
project (q3_encrypted_chat))

add_library(swapLib SHARED encryption.c)

add_executable(q3_encrypted_chat q3_encrypted_chat.c)
target_link_libraries(q3_encrypted_chat swapLib)
