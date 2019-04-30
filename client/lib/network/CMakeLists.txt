cmake_minimum_required(VERSION 3.13)
project(client_sockets C)

set(CMAKE_C_STANDARD 99)

add_executable(client_sockets test.c sockets.c sockets.h metadata.c metadata.h)