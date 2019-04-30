//
// Created by h0tw4t3r on 4/29/19.
//

// Sockets testing unit

#include "sockets.h"
#include "metadata.h"

int main() {
    int sock = socketCreate("localhost", "9304");
    player_meta_t player_meta = {
            {3, 4},
            1
    };
    uint8_t res[24];

    res[0] = 1;
    res[1] = 2;
    res[23] = 23;
    size_t len = 24;
    socketWrite(sock, res, &len);
    int rv = -1;
    while(rv == -1) {
        rv = socketRead(sock, res, sizeof(res));
    }
    printf("1");
    return 0;
}