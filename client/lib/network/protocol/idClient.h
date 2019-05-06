//
// Created by h0tw4t3r on 5/7/19.
//

#ifndef MAIN_SERVER_IDCLIENT_H
#define MAIN_SERVER_IDCLIENT_H

#include <inttypes.h>
#include <netinet/in.h>
#include <stdio.h>

#include "../../../../lib/netconf.h"
#include "../../../../lib/zdtp.h"
#include "../../../../lib/host.h"
#include "../../../../lib/client.h"

uint8_t * idClient_packUpdate(uint8_t *res);
client_t * idClient_unpackClientData(uint8_t *data, client_t *res);
host_t * idClient_unpackHostData(uint8_t *data, host_t *res);

#endif //MAIN_SERVER_IDCLIENT_H
