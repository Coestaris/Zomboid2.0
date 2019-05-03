//
// Created by h0tw4t3r on 5/2/19.
//

/*
 * Main Network Node
 *
 * TCP/IP
 */
#include "sockets.h"

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
    uint8_t running = 1;

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

    if (listen(sockfd, MAX_CONNECTS) == -1) {
        perror("listen");
        exit(1);
    }

    FD_SET(sockfd, &master_fds);
    fdmax = sockfd;

    char buff[256];

    while (running) {
        read_fds = master_fds;
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(1);
        }

        for (int i = 0; i < fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == sockfd) {
                    // handling new connections
                    addrlen = sizeof(remoteaddr);
                    newfd = accept(sockfd,
                                   &remoteaddr, &addrlen);

                    if (newfd == -1) {
                        perror("accept");
                    } else {
                        FD_SET(newfd, &master_fds);
                        if (newfd > fdmax) fdmax = newfd;
                        printf("selectserver: new connection from %s on "
                               "socket %d\n",
                               inet_ntop(remoteaddr.sa_family,
                                         &remoteaddr,
                                         buff, INET_ADDRSTRLEN),
                               newfd);
                        clients[clientsCount].uid = clientsCount;
                        memcpy(&(clients + clientsCount)->address, &remoteaddr, sizeof(sockaddr_t));
                        clients[clientsCount].sockfd = newfd;
                        clientsCount++;

                        // send packets with clients and hosts data to a new client
                        uint32_t addr_buff;
                        for (zsize_t j = 0; j < clientsCount; j++) {
                            uint8_t res[MSG_CLIENT_DATA_LENGTH];
                            identityServer_buildClientInfoPacket(&clients[i], res);
                            // send info
                            if (send(newfd, res, MSG_CLIENT_DATA_LENGTH, 0) == -1) {
                                perror("send");
                                exit(1);
                            }
                        }

                        for (zsize_t j = 0; j < hostsCount; j++) {
                            uint8_t res[MSG_HOST_DATA_LENGTH];
                            identityServer_buildHostInfoPacket(&hosts[i], res);
                            // send info
                            if (send(newfd, res, MSG_HOST_DATA_LENGTH, 0) == -1) {
                                perror("send");
                                exit(1);
                            }
                        }
                    }
                } else {
                    // identifying client uid by it's socket descriptor
                    zsize_t current_client;
                    for (current_client = 0;
                         current_client < clientsCount &&
                         clients[current_client].sockfd != sockfd;
                         current_client++);

                    if ((nbytes = recv(i, buff, sizeof buff, 0)) <= 0) {
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // connection closed
                            // TODO: destroy client by it's id and associated server node if any
                            uint8_t found = 0;
                            uint8_t cur_h;
                            for (cur_h = 0; cur_h < hostsCount; cur_h++)
                                if (hosts[cur_h].client_uid == current_client) found = 1;
                            if (found)
                                for (uint8_t j = cur_h; j < hostsCount - 1; j++) hosts[j] = hosts[j + 1];
                            for (uint8_t j = current_client; j < clientsCount - 1; j++) clients[j] = clients[j + 1];
                            printf("selectserver: socket %d hung up\n", sockfd);
                        } else {
                            perror("recv");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master_fds); // remove from master set
                    } else {
                        // we got some data from a client
                        for (zsize_t j = 0; j < current_client; j++) {

                        }
                        for (zsize_t j = (zsize_t) (current_client + 1); j < clientsCount; j++) {

                        }
                        for (int j = 0; j <= fdmax; j++) {
                            // send to everyone!
                            if (FD_ISSET(j, &master_fds)) {
                                // except the listener and ourselves
                                if (j != sockfd && j != i) {
                                    if (send(j, buff, nbytes, 0) == -1) {
                                        perror("send");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
/*
    while (running) {

        // everybody will hang on a single socket descriptor
        // and the only way to identify them - by ip address
        uint8_t recv_buff[MAX_BUFFER] = {0};
        sockaddr_in_t their_addr;
        socklen_t addr_len = sizeof(their_addr);

        if (recvfrom(listener, recv_buff, sizeof(recv_buff), 0, (sockaddr_t *) &their_addr, &addr_len) ==
            -1) {
            perror("recvfrom");
            exit(1);
        } else {
            *//*
             * TODO: Add anywhere something kind of timeout of recieved packets by user
             * We should track how many packets have been received by every user
             * and i.e. find delta of best-connected user, and worst-connected user,
             * and kick worst-connected if delta is more than some defined constant.
             *//*
            uint8_t ip_buff[INET_ADDRSTRLEN];
            printf("server: got packet from %s\n",
                   inet_ntop(their_addr.sin_family, (sockaddr_t *) &their_addr, (char *) &ip_buff,
                             sizeof(ip_buff)));
            //checking if a client is registered
            uint8_t found = 0;
            int8_t client_current = 0;
            for (uint8_t i = 0; i < clientsCount; i++)
                if (memcmp(clients + i, (sockaddr_t *) &their_addr, sizeof(sockaddr_t)) == 0) {
                    found = 1;
                    client_current = i;
                    clients[client_current].last_packet = clock();
                }
            if (!found) {
                if (clientsCount == MAX_CLIENTS) {
                    // sending a "sorry lobby is full" message
                    // ...
                } else {
                    memcpy(&(clients + clientsCount)->address, &their_addr, sizeof(sockaddr_t));
                    client_current = clientsCount;
                    clientsCount++;
                }
            }
            printf("server: packet contains \"%s\"\n", recv_buff);
            // sending messages to all except for current player
            for (uint8_t i = 0; i < client_current; i++) {
                sendUpdate(listener, clients[i].address);
            }
            for (uint8_t i = (uint8_t) (client_current + 1); i < clientsCount; i++) {
                sendUpdate(listener, clients[i].address);
            }
        }
    }*/
}