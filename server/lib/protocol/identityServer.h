//
// Created by h0tw4t3r on 5/4/19.
//

/*
 * IDP - IDENTITY TRANSMISSION PROTOCOL
 */

#ifndef MAIN_SERVER_IDENTITYSERVER_H
#define MAIN_SERVER_IDENTITYSERVER_H


#include <inttypes.h>
#include <netinet/in.h>

#include "../../../lib/netconf.h"
#include "../../../lib/zdtp.h"
#include "../../client.h"
#include "../../host.h"
/*
 * Client has:
 *  - UID - sizeof (zsize_t)
 *  - Nickname [up to 32 symbols] - 4 bytes | TODO: RESTRICT NON-LATIN SYMBOLS
 *  - Address - 1 byte
 */

#define MSG_CLIENT_DATA_LENGTH 5 + sizeof (zsize_t) // s - scalability

/*
 * Host has:
 *  - UID - sizeof (zsize_t)
 *  - Client UID - sizeof (zsize_t)
 *  - Name [up to 32 symbols] - 4 bytes | TODO: RESTRICT NON-LATIN SYMBOLS
 *  - Port - 4 bytes
 */

#define MSG_HOST_DATA_LENGTH 8 + 2 * sizeof (zsize_t)

void identityServer_buildClientInfoPacket(client_t *client, uint8_t *res);
void identityServer_buildHostInfoPacket(host_t *host, uint8_t res[MSG_HOST_DATA_LENGTH]);

#endif //MAIN_SERVER_IDENTITYSERVER_H
