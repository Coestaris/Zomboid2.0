//
// Created by maxim on 2/23/19.
//

#ifndef ZOMBOID2_SOCKETS_H
#define ZOMBOID2_SOCKETS_H

#include "../messageTypes.h"
#include "../metadata.h"
#include "../../../../lib/netconf.h"
#include "../../../../lib/idtp.h"

#define MAX_HANDLERS 100

typedef struct _network_handler {
    int messageType;
    void (*func)(char*, size_t);
} network_handler;

typedef struct {
    int sockfd;
    struct sockaddr addr;
} r_info;

r_info gameSocketCreate(char *addr, char *port);
int gameSocketWrite(r_info serv_info, uint8_t *data, size_t *len);
int gameSocketRead(int socketfd, uint8_t *res, size_t len);
int gameSocketClose(int socketfd);

int gameSocketHandlerSubscribe(network_handler *handler);
network_handler * gameSocketHandlerCreate(int messageType, void (*func)(char*, size_t));
void gameSocketHandlersClear();

#endif //ZOMBOID2_SOCKETS_H
