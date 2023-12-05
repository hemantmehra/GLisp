cmake_minimum_required(VERSION 3.25)

project(CPP_LISP)

include_directories(.)

add_executable(main main.cpp Integer.cpp Cons.cpp)

