//
// Created by h0tw4t3r on 5/4/19.
//

#include "identityServer.h"

uint64_t write_uint_n(uint64_t data, uint64_t start, uint8_t n, uint8_t *res) {
    if (n > sizeof (uint64_t)) {
        perror("serialization: wrong data size");
        exit(1);
    }
    uint64_t offset = 0x00000000000000FF;
    for (uint64_t i = start; i < start + n; i++) {
        res[i] = (uint8_t) (data && offset);
        offset <<= 2;
    }
    return start + n;
}

uint64_t write_string(uint8_t *data, uint64_t start, size_t datalen, uint8_t *res) {
    memcpy(res + start, data, datalen);
    return start + datalen;
}

uint8_t * identityServer_buildClientInfoPacket(client_t *client, uint8_t res[MSG_CLIENT_DATA_LENGTH]) {
    uint64_t total = 1;
    // filling header
    res[0] = MSGTYPE_IDENTITY_SERVER_CLIENT_DATA;
    // uid
    total = write_uint_n(client->uid, total, sizeof (zsize_t), res);
    // name
    total = write_string(client->name, total, MAX_CLIENT_NAME_LENGTH, res);
    // address
    write_uint_n(client->address.sin_addr.s_addr, total, sizeof (uint32_t), res);

    return res;
}

uint8_t * identityServer_buildHostInfoPacket(host_t *host, uint8_t res[MSG_HOST_DATA_LENGTH]) {
    uint64_t total = 1;
    // filling header
    res[0] = MSGTYPE_IDENTITY_SERVER_HOST_DATA;
    // uid
    total = write_uint_n(host->uid, total, sizeof (zsize_t), res);
    // client uid
    total = write_uint_n(host->client_uid, total, sizeof (zsize_t), res);
    // name
    total = write_string(host->name, total, MAX_HOST_NAME_LENGTH, res);
    // port
    write_uint_n(host->port, total, sizeof (uint16_t), res);

    return res;
}

uint8_t * identityServer_buildDestroyPacket(zsize_t clientUID, uint8_t isHost, zsize_t hostUID, uint8_t res[MSG_DESTROY_LENGTH]) {
    uint64_t total = 1;
    // filling header
    res[0] = MSGTYPE_IDENTITY_SERVER_CLIENT_DESTROY;
    // clientUID
    total = write_uint_n(clientUID, total, sizeof (zsize_t), res);
    // isHost
    total = write_uint_n(isHost, total, sizeof (uint8_t), res);
    // hostUID
    write_uint_n(hostUID, total, sizeof (uint8_t), res);

    return res;
}