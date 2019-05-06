cmake_minimum_required(VERSION 3.13)
project(server C)

set(CMAKE_C_STANDARD 99)

add_executable(host testHost.c host/sockets.c host/sockets.h ../../../server/logicHandler.c ../../../server/logicHandler.h ../../../server/client.c ../../../lib/client.h ../../../server/actionNotifier.c ../../../server/actionNotifier.h ../../../server/handlers/baseHandlers.c ../../../server/handlers/baseHandlers.h ../../../server/handlers/messageTypes.h ../../../lib/netconf.h)
add_executable(client testClient.c client/gameSockets.c client/gameSockets.h)
add_executable(idClient protocol/idClient.c protocol/idClient.h client/serverSockets.c client/serverSockets.h)
