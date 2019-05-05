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
#include "../../client.h"
#include "../../host.h"

/*
 * Header - 1 byte
 * Client has:
 *  - UID - sizeof (zsize_t)
 *  - Nickname [up to 32 symbols] - 32 bytes | TODO: RESTRICT NON-LATIN SYMBOLS
 *  - Address - 1 byte
 */

#define MSG_CLIENT_DATA_LENGTH 34 + sizeof (zsize_t) // s - scalability

/*
 * Header - 1 byte
 * Host has:
 *  - UID - sizeof (zsize_t)
 *  - Client UID - sizeof (zsize_t)
 *  - Name [up to 32 symbols] - 32 bytes | TODO: RESTRICT NON-LATIN SYMBOLS
 *  - Port - 4 bytes
 */

#define MSG_HOST_DATA_LENGTH 37 + 2 * sizeof (zsize_t)

/*
 * Header - 1 byte
 * Client + Host destruction packet, has:
 *  - UID of the client - sizeof (zsize_t)
 *  - isHost - 1 byte
 *  - UID of the host - sizeof (zsize-t)
 * */

#define MSG_DESTROY_LENGTH 2 + 2 * sizeof(zsize_t)

uint8_t * identityServer_buildClientInfoPacket(client_t *client, uint8_t *res);
uint8_t * identityServer_buildHostInfoPacket(host_t *host, uint8_t res[MSG_HOST_DATA_LENGTH]);
uint8_t * identityServer_buildDestroyPacket(zsize_t clientUID, uint8_t isHost, zsize_t hostUID, uint8_t res[MSG_DESTROY_LENGTH]);

#endif //MAIN_SERVER_IDENTITYSERVER_H
