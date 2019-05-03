//
// Created by maxim on 2/23/19.
//

#ifndef SERVER_SOCKETS_H
#define SERVER_SOCKETS_H

#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#include <zconf.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <asm/errno.h>

#include "../../../../lib/netconf.h"
#include "../../../../server/client.h"
#include "../../../../server/logicHandler.h"
#include "../../../../server/actionNotifier.h"

typedef struct {
    sockaddr_t address;
    time_t last_packet;
} client_t;

void setPort(uint16_t port);
int socketServerCreate(char *port);
int socketInit(void);
int socketMainloop(int listener);

#endif //SERVER_SOCKETS_H
