//
// Created by h0tw4t3r on 5/2/19.
//

#ifndef SERVER_SOCKETS_H
#define SERVER_SOCKETS_H

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
#include <netdb.h>

#include "../protocol/idServer.h"
#include "../../../lib/client.h"

#define MAX_ZNET_CLIENTS 100
#define MAX_ZNET_HOSTS 10


int socketCreate(char * port);
int socketMainLoop(int sockfd);

#endif //SERVER_SOCKETS_H
