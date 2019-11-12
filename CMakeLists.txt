cmake_minimum_required(VERSION 2.6)

project(Hashi C)
enable_testing()

set(CMAKE_INSTALL_PREFIX .)
set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

include_directories(include)
add_subdirectory(src)
add_subdirectory(sdl2-demo)
