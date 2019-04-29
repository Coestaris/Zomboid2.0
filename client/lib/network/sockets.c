//
// Created by maxim on 2/23/19.
//

#include <fcntl.h>
#include "sockets.h"
#include "messageTypes.h"
#include "metadata.h"

// CLion for some reason thinks that recv can't return 0, so

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

ssize_t buffLen = 0;
char buffer[BUFFER_SIZE];
char send_buffer[BUFFER_SIZE + sizeof(int) + 1];

network_handler* handlers[MAX_HANDLERS];
int handlersCount = 0;


int socketCreate(char *_addr, char *port) {
    /*
     * We use connect() and bind() for UDP packet's to increase performance
     * This function returns new socket fd
     */

    struct addrinfo hints, *servinfo, *p;

    int rv;
    int sockfd = -1;

    //look up for an address and open a socket
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // don't force ip4 or ip6
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo(_addr, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "ServerInfo lookup error: %s\n", gai_strerror(rv));
        exit(1);
    }

    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("Socket creation error");
            continue;
        }

        break;
    }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
        perror("connect");
        exit(1);
    }

    fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL) | O_NONBLOCK);
    freeaddrinfo(servinfo);

    if (p == NULL) {
        fprintf(stderr, "No serverinfo error - can't create socket\n");
        exit(2);
    }
    return sockfd;
}

int socketWrite(int socketfd, uint8_t *data, int *len) {
    int total = 0;
    size_t bytesleft = (size_t) *len;
    ssize_t n = -1;

    while(total < bytesleft) {
        n = send(socketfd, data + total, bytesleft, 0);
        if (n == -1) break;
        total += n;
        bytesleft -= n;
    }

    *len = total;

    return n == -1 ? -1 : 0;
}

int socketReadAttempt(int sockfd, struct timeval * timeout, uint8_t * res) {
    fd_set readfds;
    int numbytes;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);

    if (select(sockfd + 1, &readfds, NULL, NULL, timeout) == -1) {
        perror("select");
        exit(1);
    }

    // looking for data

    if(FD_ISSET(sockfd, &readfds)) {
        if ((numbytes = recv(sockfd, res, sizeof(res), 0) <= 0)) {
            if (numbytes == 0) {
                perror("connection closed");
                exit(1);
            } else {
                perror("recv");
                exit(1);
            }
            close(sockfd);
        } else {
            //got info
            return 1;
        }
    }
    return 0;
}

/*int socketsGetUpdates()
{
    //buffLen = read(fd, buffer, BUFFER_SIZE);
    if(buffLen < 0) {
        return 0;
    }

    if(buffLen != 0) {

        if(buffLen < 4) {
            perror("message is too short!");
            return 1;
        }

        int type;
        memcpy(&type, buffer, sizeof(int));

        printf("Got message with type: %i, dataLen: %li\n", type, buffLen);

        for(int i = 0; i < handlersCount; i++) {
            if(handlers[i]->messageType == type || handlers[i]->messageType == MSGTYPE__ANY) {
                handlers[i]->func(buffer + sizeof(int), buffLen - sizeof(int));
            }
        }
    }

    return 1;
}

void pushHandler(int messageType, void (*func)(char*, size_t))
{
    network_handler* nh = malloc(sizeof(network_handler));
    nh->messageType = messageType;
    nh->func = func;
    handlers[handlersCount++] = nh;
}

int socketsSend(char* buffer, size_t buffLen)
{
    if(send(fd, buffer, buffLen, 0) != buffLen) {
        perror("Send!");
        return 0;
    } else {
        return 1;
    }
}

int socketsSendMessage(int messageType, char* buffer, size_t buffLen)
{
    memcpy(send_buffer, &messageType, sizeof(int));
    if(buffer) memcpy(send_buffer + sizeof(int), buffer, (size_t)buffLen);
    return socketsSend(send_buffer, (size_t)buffLen + sizeof(int));
}*/

#pragma clang diagnostic pop