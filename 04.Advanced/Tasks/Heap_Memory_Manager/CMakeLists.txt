cmake_minimum_required(VERSION 3.28)
project(LMM C)

set(CMAKE_C_STANDARD 11)

add_executable(LMM mm.c glthread.c test_app.c)
