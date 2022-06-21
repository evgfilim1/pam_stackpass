cmake_minimum_required(VERSION 3.0)
project(pam_stackpass C)

add_library(pam_stackpass SHARED main.c)
set_target_properties(pam_stackpass PROPERTIES PREFIX "") # remove `lib` prefix

install(TARGETS pam_stackpass LIBRARY DESTINATION lib/security)
