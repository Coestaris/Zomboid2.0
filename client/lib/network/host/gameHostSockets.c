//
// Created by maxim on 2/23/19.
//

#include "gameHostSockets.h"
#include <pthread.h>

int gameHostSocketServerCreate(char *port) {
    /*
     * We use connect() for UDP packet's to increase performance
     * This function returns new socket fd
     */

    addrinfo_t hints, *clientinfo, *p;

    int rv;
    int sockfd = -1;

    // look up for an remote address and open a socket
    memset(&hints, 0, sizeof (hints));
    // using ipv4
    hints.ai_family = AF_INET;
    // using UDP protocol
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo(NULL, port, &hints, &clientinfo)) != 0) {
        fprintf(stderr, "Remote address lookup error: %s\n", gai_strerror(rv));
        exit(1);
    }

    for (p = clientinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("Socket creation attempt failed");
            continue;
        }

        int yes = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int));

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

    notifierSocketWaiting();

    // clientinfo no longer needed
    freeaddrinfo(clientinfo);

    return sockfd;
}

void sendUpdate(int sockfd, void *data, size_t length, sockaddr_t address) {
    /*
     * Here we have to create new thread were data is processing
     */
    size_t total = 0;
    ssize_t n = -1;
    size_t left = length;
    while (total < length) {
        n = sendto(sockfd, data + total, left, 0, &address, sizeof (address));
        if (n == -1) break;
        total += n;
        left -= n;
    }

    if (n == -1) {
        perror("server sendto error");
        exit(1);
    }
}

int isTimedOut(time_t timestamp) {
    return ((clock() - timestamp) / CLOCKS_PER_SEC > DISCONNECT_TIMEOUT);
}

void * _gameHostSocketMainloop(void *_args) {
    thread_args args = *(thread_args *)_args;
    int listener = args.listener;
    int *runnning = args.running;
    void **players = args.players;
    size_t playerSize = args.playerSize;

    time_t now;
    gameClientInfo_t clients[MAX_CLIENTS] = {0};
    for (int i = 0; i < MAX_CLIENTS; i++) clients[i].clientData = players[i];
    zsize_t clientsCount = 0;

    while (*runnning) {
        // everybody will hang on a single socket descriptor
        // and the only way to identify them - by ip address
        uint8_t recv_buff[MAX_BUFFER] = {0};
        sockaddr_in_t their_addr;
        socklen_t addr_len = sizeof (their_addr);

        if (recvfrom(listener, recv_buff, sizeof (recv_buff), 0, (sockaddr_t *) &their_addr, &addr_len) ==
            -1) {
            perror("recvfrom");
            exit(1);
        } else {
            uint8_t ip_buff[INET_ADDRSTRLEN];
            printf("server: got packet from %s\n",
                   inet_ntop(their_addr.sin_family, (sockaddr_t *) &their_addr, (char *) &ip_buff,
                             sizeof(ip_buff)));
            //checking if a client is registered
            uint8_t found = 0;
            int currentClient = 0;
            for (int i = 0; i < clientsCount; i++)
                if (memcmp(clients + i, (sockaddr_t *) &their_addr, sizeof (sockaddr_t)) == 0) {
                    found = 1;
                    currentClient = i;
                    clients[currentClient].lastPacket = clock();
                }
            if (!found) {
                if (clientsCount == MAX_CLIENTS) {
                    // sending a "sorry lobby is full" message
                    // ...
                } else {
                    memcpy(&(clients + clientsCount)->address, &their_addr, sizeof (sockaddr_t));
                    currentClient = clientsCount;
                    clientsCount++;
                }
            }
            printf("server: packet contains \"%s\"\n", recv_buff);
            // sending messages to all except for current player
            for (int i = 0; i < currentClient; i++) {
                if (isTimedOut(clients[i].lastPacket)) {
                    // TODO: send disconnect message
                    // removing client
                    for (int j = i; j < clientsCount - 1; j++) {
                        clients[j] = clients[j + 1];
                    }
                    currentClient--;
                    clientsCount--;
                } else
                    for(i = 0; i < clientsCount; i++) sendUpdate(listener, clients[i].clientData,
                            playerSize, clients[i].address);
            }
            for (int i = (uint8_t) (currentClient + 1); i < clientsCount; i++) {
                if (isTimedOut(clients[i].lastPacket)) {
                    // TODO: send disconnect message
                    // removing client
                    for (int j = i; j < clientsCount - 1; j++) {
                        clients[j] = clients[j + 1];
                    }
                    clientsCount--;
                } else
                    for(i = 0; i < clientsCount; i++) sendUpdate(listener, clients[i].clientData,
                            playerSize, clients[i].address);
            }
        }
    }
}

void gameHostSocketMainloop(int listenfd, int *running, void *players[MAX_CLIENTS], size_t playerSize) {
    pthread_t tid;
    thread_args args = {
            listenfd,
            running,
            players,
            playerSize
    };
    pthread_create(&tid, NULL, _gameHostSocketMainloop, (void *)&args);
    pthread_exit(NULL);
}
