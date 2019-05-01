//
// Created by maxim on 2/23/19.
//

#include <netdb.h>
#include "sockets.h"
#include "../../../lib/netconf.h"
#include "../../actionNotifier.h"

socket_client *clients[MAX_CLIENTS];

int socketInit(void) {
    for (uint8_t i = 0; i < MAX_CLIENTS; i++) {
        clients[i] = createClient();
    }

    notifierSocketInited();
    return 1;
}

int socketServerCreate(char *port) {
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

void sendUpdate(int sockfd, sockaddr_t address) {
    /*
     * Here we have to create new thread were data is processing
     */
    size_t total = 0;
    char data[5] = "cool!";
    ssize_t n = -1;
    size_t left = sizeof (data);
    while (total < 5) {
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

int socketMainloop(int listener) {
    /*   int opt = 1;
       int addrlen, new_socket, sd;
       ssize_t valread;
       ssize_t nbytes;
       struct sockaddr_in address;
       addrlen = sizeof(address);*/
/*    int fdmax;*/

    uint8_t running = 1;

    sockaddr_t clients[MAX_CLIENTS] = {0};
    uint8_t clientsCount = 0;

    while (running) {

        // everybody will hang on a single socket descriptor
        // and the only way to identify them - by ip address
        uint8_t recv_buff[MAX_BUFFER] = {0};
        sockaddr_in_t their_addr;
        socklen_t addr_len = sizeof (their_addr);

        // if no packets from user in a second - count it as a disconnect
        // 2 sec
        timeval_t timeout = {2, 0};

        if (recvfrom(listener, recv_buff, sizeof (recv_buff), 0, (sockaddr_t *) &their_addr, &addr_len) ==
            -1) {
            perror("recvfrom");
            exit(1);
        } else {
            /*
             * TODO: Add anywhere something kind of timeout of recieved packets by user
             * We should track how many packets have been received by every user
             * and i.e. find delta of best-connected user, and worst-connected user,
             * and kick worst-connected if delta is more than some defined constant.
             */
            uint8_t ip_buff[INET_ADDRSTRLEN];
            printf("server: got packet from %s\n",
                   inet_ntop(their_addr.sin_family, (sockaddr_t *) &their_addr, (char *) &ip_buff,
                             sizeof(ip_buff)));
            //checking if a client is registered
            uint8_t found = 0;
            int8_t client_current = 0;
            for (uint8_t i = 0; i < clientsCount; i++)
                if (memcmp(clients + i, (sockaddr_t *) &their_addr, sizeof (sockaddr_t)) == 0) {
                    found = 1;
                    client_current = i;
                }
            if (!found) {
                if (clientsCount == MAX_CLIENTS) {
                    // sending a "sorry lobby is full" message
                    // ...
                } else {
                    memcpy(clients + clientsCount, &their_addr, sizeof (sockaddr_t));
                    client_current = clientsCount;
                    clientsCount++;
                }
            }
            printf("server: packet contains \"%s\"\n", recv_buff);
            // sending messages to all except for current player
            for (uint8_t i = 0; i < client_current; i++) {
                sendUpdate(listener, clients[i]);
            }
            for (uint8_t i = (uint8_t) (client_current + 1); i < clientsCount; i++) {
                sendUpdate(listener, clients[i]);
            }
        }
        /* if (FD_ISSET(listener, &readfds)) {
             if ((new_socket = accept(listener, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
                 perror("accept");
                 return 0;
             }

             notifierSocketNew(new_socket, address);

             for (i = 0; i < MAX_CLIENTS; i++) {
                 if (clients[i]->sd == 0) {
                     clients[i]->sd = new_socket;
                     clients[i]->info->state = STATE_UNDEFINED;

                     notifierSocketAdded(i);
                     handleConnection(clients[i]);
                     break;
                 }
             }
         }

         for (i = 0; i < MAX_CLIENTS; i++) {
             sd = clients[i]->sd;
             if (FD_ISSET(sd, &readfds)) {
                 if ((valread = read(sd, clients[i]->buffer, BUFFER_SIZE)) == 0) {
                     clientDisconnect(clients[i]);
                 } else {
                     clients[i]->buffLen = valread;
                 }
             }
         }

         handleClients(clients);*/
    }
}