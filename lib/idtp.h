//
// Created by h0tw4t3r on 5/3/19.
//

#ifndef MAIN_SERVER_ZDTP_H
#define MAIN_SERVER_ZDTP_H
/*
 * Zomboid Data Transfer Protocol
 *
 */
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include <zconf.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <asm/errno.h>
#include "netconf.h"
#include "client.h"
#include "host.h"

#define MSGTYPE__CONNECTED -2
#define MSGTYPE__ANY -1


enum {
    MSG_ID_CLIENT_CLIENT_INIT, MSGTYPE_INIT_RES, MSGTYPE_INIT_REQ, MSG_ID_SERVER_CLIENT_DATA, MSG_ID_SERVER_CLIENT_CLOSE,
    MSG_ID_SERVER_UPDATE_START, MSG_ID_SERVER_UPDATE_END, MSG_ID_SERVER_HOST_DATA, MSG_ID_CLIENT_HOST_INIT,
    MSG_ID_SERVER_HOST_CLOSE, MSG_ID_CLIENT_UPDATE_INIT
        };


///////////////////////////////////////////////////////////////////////////

/*
 * ID Server Protocol Specification
 */

/* Client Data
 *
 * Header - 1 byte
 * Client has:
 *  - UID - sizeof (zsize_t)
 *  - isHost - 1 byte
 *  - Host UID - sizeof (zsize_t)
 *  - Nickname [up to 32 symbols] - 32 bytes | TODO: RESTRICT NON-LATIN SYMBOLS
 *  - Address - 1 byte
 */

#define MSG_ID_SERVER_CLIENT_DATA_LENGTH 35 + 2 * sizeof (zsize_t) // s - scalability

/* Host data
 *
 * Header - 1 byte
 * Host has:
 *  - UID - sizeof (zsize_t)
 *  - Name [up to 32 symbols] - 32 bytes | TODO: RESTRICT NON-LATIN SYMBOLS
 *  - Port - 4 bytes
 *  - clientsCount - sizeof (zsize_t)
 */

#define MSG_ID_SERVER_HOST_DATA_LENGTH 37 + 2 * sizeof (zsize_t)

/* Client close
 *
 * Header - 1 byte
 * Client + Host destruction packet, has:
 *  - UID of the client - sizeof (zsize_t)
 *  - isHost - 1 byte
 *  - UID of the host - sizeof (zsize-t)
 * */

#define MSG_ID_SERVER_CLIENT_CLOSE_LENGTH 2 + 2 * sizeof(zsize_t)

/*
 * Client Init
 *
 * Header - 1 byte
 *
 * - Nickname [up to 32 symbols] - 32 bytes
 */

#define MSG_ID_CLIENT_CLIENT_INIT_LENGTH 33

/*
 * Init host packet
 *
 * Header - 1 byte
 *
 * - HostName - 32 bytes
 * - Port - 2 bytes
 */

#define MSG_ID_CLIENT_HOST_INIT_LENGTH 35

/*
 * Host close packet
 *
 * Header - 1 byte
 */

#define MSG_ID_SERVER_HOST_CLOSE_LENGTH 1

/*
 * IDServer started sending data - update start packet
 *
 * Header - 1 byte
 */

#define MSG_ID_SERVER_UPDATE_START_LENGTH 1

/*
 * IDServer stopped sending data - update end packet
 *
 * Header - 1 byte
 */

#define MSG_ID_SERVER_UPDATE_END_LENGTH 1

///////////////////////////////////////////////////////////////////////////

/*,
 * ID Client Protocol Specification
 */

/*
 * Client Update packet
 *
 * Header - 1 byte
 */

#define MSG_ID_CLIENT_UPDATE_LENGTH 1

int sendAll(int sockfd, uint8_t *buff, size_t len, int flags);

uint64_t read_uint_n(const uint8_t *data, uint8_t n, uint64_t offset, void *res);
uint64_t read_string(uint8_t *data, size_t n, uint64_t offset, void *res);
uint64_t write_uint_n(uint64_t data, uint8_t n, uint64_t offset, uint8_t *res);
uint64_t write_string(uint8_t *data, size_t n, uint64_t offset, uint8_t *res);

uint8_t * idClient_packUpdate(uint8_t res[MSG_ID_CLIENT_UPDATE_LENGTH]);
uint8_t * idClient_packHostInit(uint8_t hostName[MAX_HOST_NAME_LENGTH], uint16_t port, uint8_t res[MSG_ID_CLIENT_HOST_INIT_LENGTH]);
uint8_t * idClient_packClientInit(uint8_t clientName[MAX_CLIENT_NAME_LENGTH], uint8_t res[MSG_ID_CLIENT_CLIENT_INIT_LENGTH]);
idClient_t * idClient_unpackClientData(uint8_t data[MSG_ID_SERVER_CLIENT_DATA_LENGTH], idClient_t *res);
idHost_t * idClient_unpackHostData(uint8_t data[MSG_ID_SERVER_HOST_DATA_LENGTH], idHost_t *res);
uint8_t * idClient_unpackClientInit(uint8_t data[MSG_ID_CLIENT_CLIENT_INIT_LENGTH], uint8_t res[MAX_CLIENT_NAME_LENGTH]);
uint8_t * idClient_unpackHostInit(uint8_t data[MSG_ID_CLIENT_HOST_INIT_LENGTH], uint16_t *port, uint8_t res[MAX_HOST_NAME_LENGTH]);

uint8_t * idServer_packClientData(idClient_t *client, uint8_t res[MSG_ID_SERVER_CLIENT_DATA_LENGTH]);
uint8_t * idServer_packClientClose(zsize_t clientUID, uint8_t isHost, zsize_t hostUID, uint8_t res[MSG_ID_SERVER_CLIENT_CLOSE_LENGTH]);
uint8_t * idServer_packHostData(idHost_t *host, uint8_t res[MSG_ID_SERVER_HOST_DATA_LENGTH]);
uint8_t * idServer_packHostClose(zsize_t hostUID, uint8_t res[MSG_ID_SERVER_HOST_CLOSE_LENGTH]);
uint8_t * idServer_packUpdateStart(uint8_t res[MSG_ID_SERVER_UPDATE_START_LENGTH]);
uint8_t * idServer_packUpdateEnd(uint8_t res[MSG_ID_SERVER_UPDATE_END_LENGTH]);
idClient_t * idServer_unpackClientData(uint8_t data[MAX_CLIENT_NAME_LENGTH], idClient_t *res);
idHost_t * idServer_unpackHostData(uint8_t data[MAX_HOST_NAME_LENGTH], idHost_t *res);
#endif //MAIN_SERVER_ZDTP_H
