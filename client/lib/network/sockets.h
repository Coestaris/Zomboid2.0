//
// Created by maxim on 2/23/19.
//

#ifndef ZOMBOID2_SOCKETS_H
#define ZOMBOID2_SOCKETS_H

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <memory.h>
#include <arpa/inet.h>
#include <zconf.h>

#include "messageTypes.h"

#define BUFFER_SIZE 1024
#define MAX_HANDLERS 100

typedef struct _network_handler {
    int messageType;
    void (*func)(char*, size_t);

} network_handler;

void socketsSetAddress(char* addr);
void socketsSetPort(uint16_t port);

int socketsOpen(void);
int socketsGetUpdates();

void pushHandler(int messageType, void (*func)(char*, size_t));

int socketsSend(char* buffer, size_t buffLen);
int socketsSendMessage(int msgType, char* buffer, size_t buffLen);

#endif //ZOMBOID2_SOCKETS_H
