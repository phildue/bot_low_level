cmake_minimum_required(VERSION 3.10)
project(robopi_drivers)

set(CMAKE_CXX_STANDARD 14)

set(COMPILE_FOR_ARDUINO FALSE CACHE BOOL "Set true if compile for pi")
set(COMPILE_FOR_PI FALSE CACHE BOOL "Set true if compile for pi")

add_subdirectory(lib)

add_subdirectory(bin)


