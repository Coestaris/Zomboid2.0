cmake_minimum_required(VERSION 3.13)
project(main_server C)

set(CMAKE_C_STANDARD 99)

add_executable(node lib/network/sockets.h lib/network/sockets.c lib/protocol/idServer.c lib/protocol/idServer.h ../lib/netconf.h ../lib/client.h client.c ../lib/host.h test.c ../client/lib/network/client/serverSockets.c ../client/lib/network/client/serverSockets.h)
