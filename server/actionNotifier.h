//
// Created by maxim on 2/23/19.
//

#ifndef SERVER_ACTIONNOTIFIER_H
#define SERVER_ACTIONNOTIFIER_H

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../lib/client.h"

void notifierSocketInited(void);
void notifierSocketListening(char * port);
void notifierSocketWaiting(void);
void notifierSocketNew(int socket, struct sockaddr_in addr);
void notifierSocketAdded(int index);
void notifierSocketClosed(socket_client* client);

#endif //SERVER_ACTIONNOTIFIER_H
