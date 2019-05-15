cmake_minimum_required(VERSION 3.13)
project(server C)

set(CMAKE_C_STANDARD 99)

add_executable(host testHost.c host/gameHostSockets.c host/gameHostSockets.h ../../../server/logicHandler.c ../../../server/logicHandler.h ../../../server/client.c ../../../lib/client.h ../../../server/actionNotifier.c ../../../server/actionNotifier.h ../../../server/handlers/baseHandlers.c ../../../server/handlers/baseHandlers.h ../../../server/handlers/messageTypes.h ../../../lib/netconf.h)
add_executable(client testClient.c client/gameClientSockets.c client/gameClientSockets.h)
add_executable(idClient testClient.c ../../../lib/idtp.h ../../../lib/idtp.c client/idSockets.c client/idSockets.h)
add_executable(idServer testHost.c ../../../lib/idtp.h ../../../lib/idtp.c ../../../server/lib/network/sockets.h ../../../server/lib/network/sockets.c ../../../lib/netconf.h ../../../lib/client.h ../../../server/client.c ../../../lib/host.h ../../../lib/idtp.h)
