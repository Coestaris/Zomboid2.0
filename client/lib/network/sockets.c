//
// Created by maxim on 2/23/19.
//

#include "sockets.h"
#include "messageTypes.h"
#include "metadata.h"

struct addrinfo hints, *servinfo, *p;

ssize_t buffLen = 0;
char buffer[BUFFER_SIZE];
char send_buffer[BUFFER_SIZE + sizeof(int) + 1];

network_handler* handlers[MAX_HANDLERS];
int handlersCount = 0;


int socketCreate(char *_addr, char *port) {
    /*
     * We use connect() and bind() for UDP packet's to increase performance
     */

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

    if (connect(sockfd, (const struct sockaddr *) &servinfo, sizeof servinfo) == -1) {
        perror("connect");
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

    if (p == NULL) {
        fprintf(stderr, "No serverinfo error - can't create socket\n");
        exit(2);
    }
    return sockfd;
}

int socketWrite(int socketfd, player_meta_t player_meta) {
    int total = 0;
    int byteleft = sizeof player_meta;
}

int socketRead(int sockfd) {
    fd_set readfs;
    int newfd;

    FD_ZERO(&readfs);
    FD_SET(sockfd, &readfs);

    if(select(sockfd + 1, &readfs, NULL, NULL, NULL) == -1) {
        perror("select");
        exit(-1);
    }

    newfd = accept(sockfd, )

}

int socketsGetUpdates()
{
    buffLen = read(fd, buffer, BUFFER_SIZE);
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
}
