//
// Created by h0tw4t3r on 5/4/19.
//

#include "identityServer.h"
#include "../../host.h"

uint64_t write_uintn(uint64_t data, uint64_t start, uint8_t n, uint8_t * res) {
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

uint64_t write_string(uint8_t * data, uint64_t start, size_t datalen, uint8_t *res) {
    memcpy(res + start, data, datalen);
    return start + datalen;
}

void identityServer_buildClientInfoPacket(client_t *client, uint8_t res[MSG_CLIENT_DATA_LENGTH]) {
    uint64_t total = 1;
    // filling header
    res[0] = MSGTYPE_IDENTITY_SERVER_CLIENT_DATA;
    // uid
    total = write_uintn(*client->uid, total, sizeof (zsize_t), res);
    // name
    total = write_string(client->name, total, MAX_CLIENT_NAME_LENGTH, res);
    // address
    write_uintn(client->address->sin_addr.s_addr, total, sizeof (uint32_t), res);
}

void identityServer_buildHostInfoPacket(host_t *host, uint8_t res[MSG_HOST_DATA_LENGTH]) {
    uint64_t total = 1;
    // filling header
    res[0] = MSGTYPE_IDENTITY_SERVER_HOST_DATA;
    // uid
    total = write_uintn(*host->uid, total, sizeof (zsize_t), res);
    // client uid
    total = write_uintn(*host->client_uid, total, sizeof (zsize_t), res);
    // name
    total = write_string(host->name, total, MAX_HOST_NAME_LENGTH, res);
    // port
    total = write_uintn(*host->port, total, sizeof (uint16_t), res);
}