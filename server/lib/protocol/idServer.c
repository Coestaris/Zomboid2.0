//
// Created by h0tw4t3r on 5/4/19.
//

#include "idServer.h"

uint8_t * idServer_packClientData(client_t *client, uint8_t *res) {
    uint64_t total = 1;
    res[0] = MSG_ID_SERVER_CLIENT_DATA;

    total = write_uint_n(client->uid, sizeof (zsize_t), total, res);
    total = write_uint_n(client->isHost, sizeof (uint8_t), total, res);
    total = write_uint_n(client->hostUid, sizeof (zsize_t), total, res);
    total = write_string(client->name, MAX_CLIENT_NAME_LENGTH, total, res);
    write_uint_n(client->address.sin_addr.s_addr, sizeof (uint32_t), total, res);

    return res;
}

uint8_t * idServer_packClientClose(zsize_t clientUID, uint8_t isHost, zsize_t hostUID, uint8_t *res) {
    uint64_t total = 1;

    res[0] = MSG_ID_SERVER_CLIENT_CLOSE;

    total = write_uint_n(clientUID, sizeof (zsize_t), total, res);
    total = write_uint_n(isHost, sizeof (uint8_t), total, res);
    write_uint_n(hostUID, sizeof (uint8_t), total, res);

    return res;
}

uint8_t * idServer_packHostData(host_t *host, uint8_t *res) {
    uint64_t total = 1;
    res[0] = MSG_ID_SERVER_HOST_DATA;

    total = write_uint_n(host->uid, sizeof (zsize_t), total, res);
    total = write_string(host->name, MAX_HOST_NAME_LENGTH, total, res);
    write_uint_n(host->port, sizeof (uint16_t), total, res);

    return res;
}

uint8_t * idServer_packHostClose(zsize_t hostUID, uint8_t *res) {
    uint64_t total = 1;

    res[0] = MSG_ID_SERVER_HOST_CLOSE;

    write_uint_n(hostUID, sizeof (uint8_t), total, res);

    return res;
}

client_t * idServer_unpackClientData(uint8_t *data, client_t *res) {
    uint64_t total = 1;

    total = read_uint_n(data, sizeof (zsize_t), total, &(res->uid));
    total = read_uint_n(data, sizeof (uint8_t), total, &(res->isHost));
    total = read_uint_n(data, sizeof (zsize_t), total, &(res->hostUid));
    total = read_string(data, MAX_HOST_NAME_LENGTH, total, res->name);
    read_uint_n(data, sizeof (uint16_t), total, &(res->address.sin_addr.s_addr));

    return res;
}

host_t * idServer_unpackHostData(uint8_t *data, host_t *res) {
    uint64_t total = 1;

    total = read_uint_n(data, sizeof (zsize_t), total, &(res->uid));
    total = read_string(data, MAX_HOST_NAME_LENGTH, total, res->name);
    read_uint_n(data, sizeof (uint16_t), total, &(res->port));

    return res;
}
