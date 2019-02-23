cmake_minimum_required(VERSION 3.13)
project(server C)

set(CMAKE_C_STANDARD 99)

add_executable(server main.c sockets.c sockets.h logicHandler.c logicHandler.h client.c client.h actionNotifier.c actionNotifier.h)