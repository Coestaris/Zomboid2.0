//
// Created by h0tw4t3r on 5/6/19.
//

#include "idSockets.h"

uint64_t max(uint64_t a, uint64_t b) { return a > b ? a : b; }

int idClientSocketCreate(const char *address, const char *port) {
    int sockfd = -1;
    addrinfo_t hints, *servinfo, *p;
    int rv;
    char s[256];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(address, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        printf("trying to connect to external (public) ip %s\n",
               inet_ntop(p->ai_family, (sockaddr_in_t *) p->ai_addr, s, sizeof s)
        );
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("client: connect");
            close(sockfd);
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        exit(1);
    }

    freeaddrinfo(servinfo); // all done with this structure

    return sockfd;
}

int idClientSocketWrite(int sockfd, uint8_t *buff, size_t bufflen) {
    if (sendAll(sockfd, buff, bufflen, 0) == -1) {
        perror("sendAll");
        exit(1);
    }
}

int idClientSocketRead(int sockfd, uint8_t *res, size_t reslen) {
    if (recv(sockfd, res, reslen, 0) == -1) {
        perror("recv");
        exit(1);
    }
}

int idClientSocketClose(int sockfd) {
    close(sockfd);
}

int idClientSocketClientInit(int sockfd, uint8_t clientName[MAX_CLIENT_NAME_LENGTH]) {
    uint8_t buff[MSG_ID_CLIENT_CLIENT_INIT_LENGTH];

    return idClientSocketWrite(sockfd, idClient_packClientInit(clientName, buff), MSG_ID_CLIENT_CLIENT_INIT_LENGTH);
}

int idClientSocketHostInit(int sockfd, uint8_t *hostName, uint16_t port) {
    uint8_t buff[MSG_ID_CLIENT_HOST_INIT_LENGTH];

    return idClientSocketWrite(sockfd, idClient_packHostInit(hostName, port, buff), MSG_ID_CLIENT_HOST_INIT_LENGTH);
}

int idClientSocketUpdateData(int sockfd, client_t *clients, zsize_t *clientsCount,
                             host_t *hosts, zsize_t *hostsCount, void (*spinnerCb)(uint8_t show)) {

    fd_set masterfds, readfds;
    ssize_t rv;
    uint8_t running = 1;
    size_t buffSize = max(MSG_ID_SERVER_HOST_DATA, MSG_ID_SERVER_CLIENT_DATA);
    uint8_t buff[buffSize];
    if (sendAll(sockfd, idClient_packUpdate(buff), MSG_ID_CLIENT_UPDATE_LENGTH, 0) == -1) {
        perror("sendAll");
        exit(1);
    }

    spinnerCb(1);

    timeval_t timeout = { MONITORING_TIMEOUT, 0 };
    FD_ZERO(&readfds);
    FD_ZERO(&masterfds);
    FD_SET(sockfd, &masterfds);

    while(running) {
        readfds = masterfds;
        if (select(sockfd + 1, &readfds, NULL, NULL, &timeout) == -1) {
            perror("select");
            exit(1);
        } else {
            if (FD_ISSET(sockfd, &readfds)) {
                if ((rv = recv(sockfd, buff, buffSize, 0)) <= 0) {
                    if (rv == 0) {
                        perror("IdentityServer closed the connection");
                        exit(1);
                    } else {
                        perror("recv");
                        exit(1);
                    }
                } else {
                    // receiving data here
                    // if there's an update end metapackage - stop the loop
                    switch (buff[0]) {
                        case MSG_ID_SERVER_UPDATE_START:
                            memset(clients, 0, *clientsCount * sizeof (client_t));
                            *clientsCount = 0;
                            memset(hosts, 0, *hostsCount * sizeof (host_t));
                            *hostsCount = 0;
                        case MSG_ID_SERVER_UPDATE_END:
                            running = 0;
                            break;
                        case MSG_ID_SERVER_CLIENT_DATA:
                            idClient_unpackClientData(buff, &clients[*clientsCount]);
                            (*clientsCount)++;
                            break;
                        case MSG_ID_SERVER_HOST_DATA:
                            idClient_unpackHostData(buff, &hosts[*hostsCount]);
                            (*hostsCount)++;
                        default: break;
                    }
                }
            }
        }
    }
}