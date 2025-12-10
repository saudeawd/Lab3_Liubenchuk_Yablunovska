cmake_minimum_required(VERSION 3.11)
project(Strings LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
include_directories(.)

# library
add_library(Strings SHARED mystring.cpp mystring_c.cpp)

# main c++
add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE Strings)

# main c
add_executable(MainC main.c)
target_link_libraries(MainC PRIVATE Strings)

add_executable(Task3 task3.cpp)
target_link_libraries(Task3 PRIVATE Strings)