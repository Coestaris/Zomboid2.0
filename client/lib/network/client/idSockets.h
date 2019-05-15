//
// Created by h0tw4t3r on 5/6/19.
//

#ifndef MAIN_SERVER_SERVERSOCKETS_H
#define MAIN_SERVER_SERVERSOCKETS_H

#include "../messageTypes.h"
#include "../metadata.h"
#include "../../../../lib/netconf.h"
#include "../../../../lib/idtp.h"
#include "../../../../lib/client.h"
#include "../../../../lib/host.h"

int idClientSocketCreate(const char *address, const char *port);
int idClientSocketWrite(int sockfd, uint8_t *buff, size_t bufflen);
int idClientSocketRead(int sockfd, uint8_t *res, size_t reslen);
int idClientSocketClose(int sockfd);
int idClientSocketUpdateData(int sockfd, idClient_t *clients, zsize_t *clientsCount,
                             idHost_t *hosts, zsize_t *hostsCount, void (*spinnerCb)(uint8_t show));
int idClientSocketClientInit(int sockfd, uint8_t *clientName);
int idClientSocketHostInit(int sockfd, uint8_t *hostName, uint16_t port);


#endif //MAIN_SERVER_SERVERSOCKETS_H
