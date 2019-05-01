cmake_minimum_required(VERSION 3.13)
project(server C)

set(CMAKE_C_STANDARD 99)

add_executable(server main.c lib/network/sockets.c lib/network/sockets.h logicHandler.c logicHandler.h client.c client.h actionNotifier.c actionNotifier.h handlers/baseHandlers.c handlers/baseHandlers.h handlers/messageTypes.h ../lib/netconf.h)
add_executable(client_sockets ../client/lib/network/test.c ../client/lib/network/sockets.c ../client/lib/network/sockets.h ../client/lib/network/metadata.c ../client/lib/network/metadata.h)
