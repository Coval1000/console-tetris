cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_STANDARD 11)

set( CMAKE_CXX_FLAGS_DEBUG 	"${CMAKE_CXX_FLAGS_DEBUG} -d -g3 -gdb3 -o0 -Wall")
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -o2 -Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT "tetris")

project(${PROJECT})

add_subdirectory(ConsoleApplication4)
