//
// Created by maxim on 2/23/19.
//

#ifndef ZOMBOID2_SOCKETS_H
#define ZOMBOID2_SOCKETS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "messageTypes.h"

#define BUFFER_SIZE 1024
#define MAX_HANDLERS 100

typedef struct _network_handler {
    int messageType;
    void (*func)(char*, size_t);

} network_handler;

int socketCreate(char *addr, char *port);

int socketsOpen(void);
int socketsGetUpdates();

void pushHandler(int messageType, void (*func)(char*, size_t));

int socketsSend(char* buffer, size_t buffLen);
int socketsSendMessage(int msgType, char* buffer, size_t buffLen);

#endif //ZOMBOID2_SOCKETS_H
