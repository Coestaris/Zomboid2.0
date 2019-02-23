//
// Created by maxim on 2/23/19.
//

#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <zconf.h>
#include <arpa/inet.h>

#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#define BUFFER_SIZE 1025
#define MAX_CLIENTS 30

typedef struct _socket_client {
    int sd;

    char buffer[BUFFER_SIZE];
    ssize_t buffLen;

} socket_client;

int clientActive(socket_client* client);
int clientRecData(socket_client* client);

int clientSend(socket_client* client, char* buffer, ssize_t buffLen);
int clientDisconnect(socket_client* client);

#endif //SERVER_CLIENT_H
