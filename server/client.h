//
// Created by maxim on 2/23/19.
//

#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <stdlib.h>
#include <memory.h>

#define BUFFER_SIZE 1025
#define MAX_CLIENTS 30

#define MAX_CLIENT_NAME_LENGTH 32
#define STATE_EMPTY 0
#define STATE_UNDEFINED 1
#define STATE_INITED 2

#include "../lib/netconf.h"
#include <netinet/in.h>
typedef struct {
    zsize_t uid;
    uint8_t name[MAX_CLIENT_NAME_LENGTH];
    sockaddr_in_t address;
    int sockfd;
} client_t;


typedef struct _client_info {
    int state;
    char* name;
} client_info;

typedef struct _socket_client {
    int sd;

    char buffer[BUFFER_SIZE];
    ssize_t buffLen;
    client_info* info;

} socket_client;

socket_client* createClient(void);

#endif //SERVER_CLIENT_H
