//
// Created by h0tw4t3r on 5/7/19.
//

#include "idClient.h"

uint8_t * idClient_packUpdate(uint8_t *res) {
    res[0] = MSG_ID_CLIENT_UPDATE_INIT;

    return res;
}

client_t * idClient_unpackClientData(uint8_t *data, client_t *res) {
    uint64_t total = 1;

    total = read_uint_n(data, sizeof (zsize_t), total, &(res->uid));
    total = read_uint_n(data, sizeof (uint8_t), total, &(res->isHost));
    total = read_uint_n(data, sizeof (zsize_t), total, &(res->hostUid));
    total = read_string(data, MAX_HOST_NAME_LENGTH, total, res->name);
    read_uint_n(data, sizeof (uint16_t), total, &(res->address.sin_addr.s_addr));

    return res;
}

host_t * idClient_unpackHostData(uint8_t *data, host_t *res) {
    uint64_t total = 1;

    total = read_uint_n(data, sizeof (zsize_t), total, &(res->uid));
    total = read_string(data, MAX_HOST_NAME_LENGTH, total, res->name);
    read_uint_n(data, sizeof (uint16_t), total, &(res->port));

    return res;
}