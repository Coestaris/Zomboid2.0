//
// Created by h0tw4t3r on 5/3/19.
//


/*
 * Zomboid Data Transfer Protocol
 *
 * MSGTYPE - 1 byte
 * clientID - 1 byte
 * hostID - 1 byte
 * DATA - 14 bytes
 */

#include "netconf.h"

#define MSGTYPE__CONNECTED -2
#define MSGTYPE__ANY -1

#define MSGTYPE_INIT_CLIENT 1
#define MSGTYPE_INIT_HOST 2
#define MSGTYPE_INIT_RES 3
#define MSGTYPE_INIT_REQ 4

#define MSGTYPE_IDENTITY_SERVER_CLIENT_DATA 5
#define MSGTYPE_IDENTITY_SERVER_CLIENT_DESTROY 6
#define MSGTYPE_IDENTITY_SERVER_HOST_DATA 7

typedef struct {
    uint8_t msgType;
    uint8_t clientID;
    uint8_t hostID;
    uint8_t data[DATA_LENGTH];
};

#ifndef MAIN_SERVER_ZDTP_H
#define MAIN_SERVER_ZDTP_H

#endif //MAIN_SERVER_ZDTP_H
