cmake_minimum_required(VERSION 2.8)

project(owl-preprocessor)

set(CMAKE_C_FLAGS "-O2 -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wpointer-arith -Wtype-limits -Wempty-body -Wno-logical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -std=gnu99")

include_directories(./) # Access to headers from subdirectories

add_executable(owl main.c)

# add_subdirectory(tests)

