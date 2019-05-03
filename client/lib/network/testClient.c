//
// Created by h0tw4t3r on 4/29/19.
//

// Sockets testing unit

#include "client/sockets.h"
#include "metadata.h"

int main() {
    r_info info = socketCreate("localhost", "9305");
    uint8_t res[24];

    res[0] = 1;
    res[1] = 2;
    res[23] = 23;
    size_t len = 24;
    socketWrite(info, res, &len);
    int rv = -1;
    while(rv == -1) {
        rv = socketRead(info.sockfd, res, sizeof(res));
    }
    socketClose(info.sockfd);
    return 0;
}