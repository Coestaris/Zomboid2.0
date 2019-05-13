//
// Created by h0tw4t3r on 5/6/19.
//

#include "lib/network/sockets.h"

int main() {
    int sockfd = socketCreate("25565");
    socketMainLoop(sockfd);
    return 0;
}