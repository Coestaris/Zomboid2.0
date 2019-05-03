//
// Created by maxim on 2/23/19.
//

#ifndef ZOMBOID2_SOCKETS_H
#define ZOMBOID2_SOCKETS_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/select.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include "../messageTypes.h"
#include "../metadata.h"
#include "../../../../lib/netconf.h"

#define MAX_HANDLERS 100

typedef struct _network_handler {
    int messageType;
    void (*func)(char*, size_t);

} network_handler;

typedef struct {
    int sockfd;
    struct sockaddr addr;
} r_info;

r_info socketCreate(char *addr, char *port);
int socketWrite(r_info serv_info, uint8_t *data, size_t *len);
int socketRead(int socketfd, uint8_t *res, size_t len);
int socketClose(int socketfd);

int socketsOpen(void);
int socketsGetUpdates();

void pushHandler(int messageType, void (*func)(char*, size_t));

int socketsSend(char *buffer, size_t buffLen);
int socketsSendMessage(int msgType, char *buffer, size_t buffLen);

#endif //ZOMBOID2_SOCKETS_H
