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