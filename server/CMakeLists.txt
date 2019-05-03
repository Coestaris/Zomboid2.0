cmake_minimum_required(VERSION 3.13)
project(main_server C)

set(CMAKE_C_STANDARD 99)

add_executable(node lib/network/sockets.h lib/network/sockets.c lib/protocol/identityServer.c lib/protocol/identityServer.h ../lib/netconf.h client.h client.c host.h)
