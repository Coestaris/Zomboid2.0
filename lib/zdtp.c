//
// Created by h0tw4t3r on 5/3/19.
//

#include "zdtp.h"

uint64_t read_uint_n(const uint8_t *data, uint8_t n, uint64_t offset, void *res) {
    if (n > sizeof (uint64_t)) {
        perror("serialization: wrong data size");
        exit(1);
    }
    for (uint64_t i = offset; i < offset + n; i++)
        *(uint64_t *)res |= data[i] << 8 * (i - offset);
    return offset + n;
}

uint64_t read_string(uint8_t *data, size_t n, uint64_t offset, void *res) {
    memcpy(res, data + offset, n);
    return offset + n;
}

uint64_t write_uint_n(uint64_t data, uint8_t n, uint64_t offset, uint8_t *res) {
    if (n > sizeof (uint64_t)) {
        perror("serialization: wrong data size");
        exit(1);
    }
    for (uint64_t i = offset; i < offset + n; i++)
        res[i] = (uint8_t) (data >> 8 * (i - offset));
    return offset + n;
}

uint64_t write_string(uint8_t *data, size_t n, uint64_t offset, uint8_t *res) {
    memcpy(res + offset, data, n);
    return offset + n;
}

int sendAll(int sockfd, uint8_t *buff, size_t len, int flags) {
    size_t total = 0;
    ssize_t n = -1;
    size_t left = len;

    while (total < len) {
        n = send(sockfd, buff + total, left, flags);
        if (n == -1) {
            perror("sendAll");
            exit(1);
        };
        total += n;
        left -= n;
    }
    // in case of error, we will know how many bytes were really sent
    len = total;

    return n == -1 ? -1 : 0;
}

uint8_t * idServer_packClientData(client_t *client, uint8_t res[MSG_ID_SERVER_CLIENT_DATA_LENGTH]) {
    uint64_t total = 1;
    res[0] = MSG_ID_SERVER_CLIENT_DATA;

    total = write_uint_n(client->uid, sizeof (zsize_t), total, res);
    total = write_uint_n(client->isHost, sizeof (uint8_t), total, res);
    total = write_uint_n(client->hostUid, sizeof (zsize_t), total, res);
    total = write_string(client->name, MAX_CLIENT_NAME_LENGTH, total, res);
    write_uint_n(client->address.sin_addr.s_addr, sizeof (uint32_t), total, res);

    return res;
}

uint8_t * idServer_packClientClose(zsize_t clientUID, uint8_t isHost,
        zsize_t hostUID, uint8_t res[MSG_ID_SERVER_CLIENT_CLOSE_LENGTH]) {
    uint64_t total = 1;

    res[0] = MSG_ID_SERVER_CLIENT_CLOSE;

    total = write_uint_n(clientUID, sizeof (zsize_t), total, res);
    total = write_uint_n(isHost, sizeof (uint8_t), total, res);
    write_uint_n(hostUID, sizeof (uint8_t), total, res);

    return res;
}

uint8_t * idServer_packHostData(host_t *host, uint8_t res[MSG_ID_SERVER_HOST_DATA_LENGTH]) {
    uint64_t total = 1;
    res[0] = MSG_ID_SERVER_HOST_DATA;

    total = write_uint_n(host->uid, sizeof (zsize_t), total, res);
    total = write_string(host->name, MAX_HOST_NAME_LENGTH, total, res);
    write_uint_n(host->port, sizeof (uint16_t), total, res);

    return res;
}

uint8_t * idServer_packHostClose(zsize_t hostUID, uint8_t res[MSG_ID_SERVER_HOST_CLOSE_LENGTH]) {
    uint64_t total = 1;

    res[0] = MSG_ID_SERVER_HOST_CLOSE;

    write_uint_n(hostUID, sizeof (uint8_t), total, res);

    return res;
}

client_t * idServer_unpackClientData(uint8_t data[MSG_ID_SERVER_CLIENT_DATA_LENGTH], client_t *res) {
    uint64_t total = 1;

    total = read_uint_n(data, sizeof (zsize_t), total, &(res->uid));
    total = read_uint_n(data, sizeof (uint8_t), total, &(res->isHost));
    total = read_uint_n(data, sizeof (zsize_t), total, &(res->hostUid));
    total = read_string(data, MAX_HOST_NAME_LENGTH, total, res->name);
    read_uint_n(data, sizeof (uint16_t), total, &(res->address.sin_addr.s_addr));

    return res;
}

host_t * idServer_unpackHostData(uint8_t data[MSG_ID_SERVER_HOST_DATA_LENGTH], host_t *res) {
    uint64_t total = 1;

    total = read_uint_n(data, sizeof (zsize_t), total, &(res->uid));
    total = read_string(data, MAX_HOST_NAME_LENGTH, total, res->name);
    read_uint_n(data, sizeof (uint16_t), total, &(res->port));

    return res;
}

uint8_t * idClient_packUpdate(uint8_t *res) {
    res[0] = MSG_ID_CLIENT_UPDATE_INIT;

    return res;
}

client_t * idClient_unpackClientData(uint8_t data[MSG_ID_SERVER_CLIENT_DATA_LENGTH], client_t *res) {
    uint64_t total = 1;

    total = read_uint_n(data, sizeof (zsize_t), total, &(res->uid));
    total = read_uint_n(data, sizeof (uint8_t), total, &(res->isHost));
    total = read_uint_n(data, sizeof (zsize_t), total, &(res->hostUid));
    total = read_string(data, MAX_HOST_NAME_LENGTH, total, res->name);
    read_uint_n(data, sizeof (uint16_t), total, &(res->address.sin_addr.s_addr));

    return res;
}

host_t * idClient_unpackHostData(uint8_t data[MSG_ID_SERVER_HOST_DATA_LENGTH], host_t *res) {
    uint64_t total = 1;

    total = read_uint_n(data, sizeof (zsize_t), total, &(res->uid));
    total = read_string(data, MAX_HOST_NAME_LENGTH, total, res->name);
    read_uint_n(data, sizeof (uint16_t), total, &(res->port));

    return res;
}

uint8_t * idClient_packHostInit(uint8_t hostName[MAX_HOST_NAME_LENGTH], uint16_t port, uint8_t res[MSG_ID_CLIENT_HOST_INIT_LENGTH]) {
    uint64_t total = 1;
    res[0] = MSG_ID_CLIENT_HOST_INIT;

    total = write_string(hostName, MAX_HOST_NAME_LENGTH, total, res);
    write_uint_n(port, sizeof (uint16_t), total, res);

    return res;
}

uint8_t * idClient_unpackHostInit(uint8_t data[MSG_ID_CLIENT_HOST_INIT_LENGTH], uint16_t * port, uint8_t res[MAX_HOST_NAME_LENGTH]) {
    uint64_t total = 1;

    total = read_string(data, MAX_HOST_NAME_LENGTH, total, res);
    read_uint_n((const uint8_t *) &port, sizeof (uint16_t), total, data);

    return res;
}

uint8_t * idClient_packClientInit(uint8_t clientName[MAX_CLIENT_NAME_LENGTH], uint8_t res[MSG_ID_CLIENT_CLIENT_INIT_LENGTH]) {
    uint64_t total = 1;
    res[0] = MSG_ID_CLIENT_CLIENT_INIT;

    write_string(clientName, MAX_CLIENT_NAME_LENGTH, total, res);

    return res;
}

uint8_t * idClient_unpackClientInit(uint8_t data[MSG_ID_CLIENT_CLIENT_INIT_LENGTH], uint8_t res[MAX_CLIENT_NAME_LENGTH]) {
    uint64_t total = 1;

    read_string(data, MAX_CLIENT_NAME_LENGTH, total, res);

    return res;
}

uint8_t * idServer_packUpdateStart(uint8_t res[MSG_ID_SERVER_UPDATE_START_LENGTH]) {
    res[0] = MSG_ID_SERVER_UPDATE_START;

    return res;
}

uint8_t * idServer_packUpdateEnd(uint8_t res[MSG_ID_SERVER_UPDATE_END_LENGTH]) {
    res[0] = MSG_ID_SERVER_UPDATE_END;

    return res;
}