//
// Created by maxim on 2/23/19.
//

#ifndef SERVER_SOCKETS_H
#define SERVER_SOCKETS_H

#include "../../../../lib/netconf.h"
#include "../../../../lib/zdtp.h"
#include "../../../../lib/client.h"
#include "../../../../server/logicHandler.h"
#include "../../../../server/actionNotifier.h"

typedef struct {
    sockaddr_t address;
    time_t last_packet;
} player_t;

void setPort(uint16_t port);
int socketServerCreate(char *port);
int socketInit(void);
int socketMainloop(int listener);

#endif //SERVER_SOCKETS_H
