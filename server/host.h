//
// Created by h0tw4t3r on 5/4/19.
//

#ifndef MAIN_SERVER_HOST_H
#define MAIN_SERVER_HOST_H

#include "../lib/netconf.h"

#define MAX_HOST_NAME_LENGTH 32

typedef struct {
    zsize_t uid;
    zsize_t client_uid;
    uint8_t name[MAX_HOST_NAME_LENGTH];
    uint16_t port;
} host_t;

#endif //MAIN_SERVER_HOST_H
