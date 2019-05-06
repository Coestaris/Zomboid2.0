//
// Created by h0tw4t3r on 5/4/19.
//

/*
 * ITP - IDENTITY TRANSMISSION PROTOCOL
 */

#ifndef MAIN_SERVER_IDENTITYSERVER_H
#define MAIN_SERVER_IDENTITYSERVER_H


#include <inttypes.h>
#include <netinet/in.h>
#include <stdio.h>

#include "../../../lib/netconf.h"
#include "../../../lib/zdtp.h"
#include "../../../lib/client.h"
#include "../../../lib/host.h"


uint8_t * idServer_packClientData(client_t *client, uint8_t *res);
uint8_t * idServer_packClientClose(zsize_t clientUID, uint8_t isHost, zsize_t hostUID, uint8_t *res);
uint8_t * idServer_packHostData(host_t *host, uint8_t *res);
uint8_t * idServer_packHostClose(zsize_t hostUID, uint8_t *res);
client_t * idServer_unpackClientData(uint8_t *data, client_t *res);
host_t * idServer_unpackHostData(uint8_t *data, host_t *res);

#endif //MAIN_SERVER_IDENTITYSERVER_H
