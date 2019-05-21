cmake_minimum_required(VERSION 3.9)
project(main_server C)

set(CMAKE_C_STANDARD 99)

add_executable(node lib/network/sockets.h lib/network/sockets.c ../lib/idtp.h ../lib/idtp.c ../lib/netconf.h ../lib/client.h client.c ../lib/host.h test.c ../client/lib/network/client/idSockets.c ../client/lib/network/client/idSockets.h)
