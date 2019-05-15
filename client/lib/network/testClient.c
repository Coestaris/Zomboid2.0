//
// Created by h0tw4t3r on 4/29/19.
//

// Sockets testing unit

#include "client/idSockets.h"
#include "client/gameSockets.h"
#include "metadata.h"

void fakeSpinner(int state){};

int main() {
    int sockfd = idClientSocketCreate("localhost", "25565");

    idClientSocketClientInit(sockfd, "username");

    idClient_t clients[255];
    idHost_t hosts[255];
    zsize_t hostsCount, clientsCount;
    uint8_t buff[1024];

    for (int i = 0; i < 5; i++) {
        idClientSocketUpdateData(sockfd, clients, &clientsCount, hosts, &hostsCount, fakeSpinner);
        idClientSocketRead(sockfd, buff, 1024);
    }

    idClientSocketClose(sockfd);
    return 0;
}