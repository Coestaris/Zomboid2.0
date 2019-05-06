//
// Created by h0tw4t3r on 5/2/19.
//

/*
 * Main Network Node
 *
 * ITP/TCP
 */

#include "sockets.h"

// probably could be useful for multiple id-servers...
void bufferHandler(uint8_t *_buff, zsize_t _currentClient, client_t *_clients, zsize_t *_clientsCount,
        host_t *_hosts, zsize_t *_hostsCount) {
    // reading header
    switch (_buff[0]) {
        case MSG_ID_SERVER_HOST_DATA:
            idServer_unpackHostData(_buff, &_hosts[*_hostsCount]);
            (*_hostsCount)++;
            break;
        case MSG_ID_SERVER_HOST_CLOSE:
            ;// send everybody that host is down
            uint8_t res[MSG_ID_SERVER_HOST_CLOSE_LENGTH];
            idServer_packHostClose(_clients[_currentClient].hostUid, res);
            zsize_t i;
            for (i = 0; i < _currentClient; i++) {
                if (send(_clients[i].sockfd, res, MSG_ID_SERVER_CLIENT_CLOSE_LENGTH, 0) == -1) {
                    perror("send");
                    exit(1);
                }
            }
            for (i = (zsize_t) (_currentClient + 1); i < *_clientsCount; i++) {
                if (send(_clients[i].sockfd, res, MSG_ID_SERVER_CLIENT_CLOSE_LENGTH, 0) == -1) {
                    perror("send");
                    exit(1);
                }
            }

            // looking up for the host and deleting it
            zsize_t cur_h;
            for (cur_h = 0;
                (cur_h < *_hostsCount) && (_hosts[cur_h].uid != _clients[_currentClient].uid); cur_h++);
            for (zsize_t j = cur_h; j < *_hostsCount - 1; j++) _hosts[j] = _hosts[j + 1];
            (*_hostsCount)--;
            break;
        default:
            break;
    }
}

int socketCreate(char *port) {
    addrinfo_t hints, *nodeinfo, *p;

    int rv;
    int sockfd = -1;
    int yes = 1;

    // look up for an remote address and open a socket
    memset(&hints, 0, sizeof(hints));
    // using ipv4
    hints.ai_family = AF_INET;
    // using UDP protocol
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(NULL, port, &hints, &nodeinfo)) != 0) {
        fprintf(stderr, "Remote address lookup error: %s\n", gai_strerror(rv));
        exit(1);
    }

    for (p = nodeinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("Socket creation attempt failed");
            continue;
        }

        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("Bind server error");
            exit(1);
        }

        break;
    }

    if (p == NULL) {
        perror("Failed to create socket");
        exit(1);
    }

    freeaddrinfo(nodeinfo);

    return sockfd;
}

int socketMainLoop(int sockfd) {
    fd_set master_fds;
    fd_set read_fds;
    int fdmax;
    int newfd;

    client_t clients[MAX_ZNET_CLIENTS] = {0};
    host_t hosts[MAX_ZNET_HOSTS] = {0};
    uint8_t clientsCount = 0;
    uint8_t hostsCount = 0;

    ssize_t nbytes;
    sockaddr_t remoteaddr;
    socklen_t addrlen;

    FD_ZERO(&master_fds);
    FD_ZERO(&read_fds);

    if (listen(sockfd, MAX_ZNET_CLIENTS) == -1) {
        perror("listen");
        exit(1);
    }

    FD_SET(sockfd, &master_fds);
    fdmax = sockfd;

    while (1) {
        read_fds = master_fds;
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(1);
        }

        for (int sockIt = 0; sockIt <= fdmax; sockIt++) {
            if (FD_ISSET(sockIt, &read_fds)) {
                if (sockIt == sockfd) {
                    // handling new connections
                    addrlen = sizeof(remoteaddr);
                    newfd = accept(sockfd,
                                   &remoteaddr, &addrlen);

                    if (newfd == -1) {
                        perror("accept");
                    } else {
                        FD_SET(newfd, &master_fds);
                        if (newfd > fdmax) fdmax = newfd;
                        clients[clientsCount].uid = clientsCount;
                        memcpy(&(clients + clientsCount)->address, &remoteaddr, sizeof(sockaddr_t));
                        clients[clientsCount].sockfd = newfd;
                        clientsCount++;

                        // SYNCHRONIZATION IS HERE

                        // send data about existing clients and hosts to a new client
                        // and at the same time send new client data to existing clients
                        uint8_t buffClientData[MSG_ID_SERVER_CLIENT_DATA_LENGTH];
                        uint8_t buffHostData[MSG_ID_SERVER_HOST_DATA_LENGTH];
                        for (zsize_t j = 0; j < clientsCount - 1; j++) {
                            // send info to a new client
                            if (sendAll(newfd,
                                     idServer_packClientData(&clients[j], buffClientData),
                                     MSG_ID_SERVER_CLIENT_DATA_LENGTH, 0) == -1) {

                                perror("send");
                                exit(1);
                            }
                            if (sendAll(clients[j].sockfd,
                                     idServer_packClientData(&clients[clientsCount - 1], buffClientData),
                                     MSG_ID_SERVER_CLIENT_DATA_LENGTH, 0) == -1) {

                                perror("send");
                                exit(1);
                            }
                        }

                        for (zsize_t j = 0; j < hostsCount; j++) {
                            idServer_packHostData(&hosts[j], buffHostData);
                            // send info
                            if (sendAll(newfd, buffHostData, MSG_ID_SERVER_HOST_DATA_LENGTH, 0) == -1) {
                                perror("send");
                                exit(1);
                            }
                        }
                    }
                } else {
                    // identifying client uid by it's socket descriptor
                    zsize_t currentClient;
                    uint8_t buff[MAX_BUFFER];
                    for (currentClient = 0;
                         currentClient < clientsCount &&
                         clients[currentClient].sockfd != sockIt;
                         currentClient++);

                    if ((nbytes = recv(sockIt, buff, sizeof buff, 0)) <= 0) {
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // connection closed
                            // TODO: destroy client by it's id and associated server node if any
                            // sending packets to destroy client and associated host to all existing clients

                            if (clients[currentClient].isHost) {
                                zsize_t cur_h;
                                for (cur_h = 0;
                                     (cur_h < hostsCount) && (hosts[cur_h].uid != clients[currentClient].uid); cur_h++);
                                for (zsize_t j = cur_h; j < hostsCount - 1; j++) hosts[j] = hosts[j + 1];
                                hostsCount--;
                            }

                            // Synchronizing between other clients
                            // Creating close-packet
                            uint8_t packet[MSG_ID_SERVER_CLIENT_CLOSE_LENGTH];
                            idServer_packClientClose(currentClient,
                                                     clients[currentClient].isHost,
                                                     clients[currentClient].hostUid,
                                                     packet);

                            for (uint8_t j = currentClient; j < clientsCount - 1; j++) clients[j] = clients[j + 1];
                            clientsCount--;

                            for (zsize_t j = 0; j < clientsCount; j++) {
                                if (sendAll(clients[j].sockfd, packet, MSG_ID_SERVER_CLIENT_CLOSE_LENGTH, 0) == -1) {
                                    perror("send");
                                    exit(1);
                                }
                            }

                            printf("selectserver: socket %d hung up\n", sockfd);
                        } else {
                            perror("recv");
                        }
                        close(sockIt); // bye!
                        FD_CLR(sockIt, &master_fds); // remove from master set
                    } /*else {
                        // parsing client
                        for (zsize_t j = 0; j < currentClient; j++) {
                            bufferHandler(buff, j, clients, &clientsCount, hosts, &hostsCount);
                        }
                        for (zsize_t j = (zsize_t) (currentClient + 1); j < clientsCount; j++) {
                            bufferHandler(buff, j, clients, &clientsCount, hosts, &hostsCount);
                        }
                    }*/
                }
            }
        }
    }
    return 1;
}