//
// Created by maxim on 2/23/19.
//

#ifndef SERVER_LOGICHANDLER_H
#define SERVER_LOGICHANDLER_H

#include <memory.h>
#include <zconf.h>

#include "../lib/client.h"
#include "actionNotifier.h"
#include "handlers/messageTypes.h"

#define MAX_HANDLERS 100

typedef struct _msg_handler {
    int messageType;
    void (*func)(socket_client*, char*, size_t);

} message_handler;

void handleClients(socket_client** clients);
int handleConnection(socket_client* client);

int clientActive(socket_client* client);
int clientRecData(socket_client* client);
int clientSend(socket_client* client, char* buffer, ssize_t buffLen);
int clientDisconnect(socket_client* client);

void clientSendMessage(socket_client* client, int messageType, char* buffer, ssize_t buffLen);
void pushHandler(int messageType, void (*func)(socket_client*, char*, size_t));

#endif //SERVER_LOGICHANDLER_H
