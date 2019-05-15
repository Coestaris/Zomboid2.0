//
// Created by maxim on 2/23/19.
//

#ifndef SERVER_SOCKETS_H
#define SERVER_SOCKETS_H

#include "../../../../lib/netconf.h"
#include "../../../../lib/idtp.h"
#include "../../../../lib/client.h"
#include "../../../../server/logicHandler.h"
#include "../../../../server/actionNotifier.h"

typedef struct {
    sockaddr_t address;
    time_t lastPacket;
    void *clientData;
} gameClientInfo_t;

typedef struct {
    int listener;
    int *running;
    void *players;
    size_t playerSize;
} thread_args;

void gameHostSetPort(uint16_t port);
int gameHostSocketServerCreate(char *port);
void gameHostSocketMainloop(int listenfd, int *runnning, void *players[MAX_CLIENTS], size_t playerSize);

#endif //SERVER_SOCKETS_H
