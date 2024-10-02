cmake_minimum_required(VERSION 3.29)
project(clox C)

set(CMAKE_C_STANDARD 11)

add_executable(clox src/main.c
        src/common.h
        src/chunk.c
        src/chunk.h
        src/memory.c
        src/memory.h
        src/debug.c
        src/debug.h
)
