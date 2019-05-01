//
// Created by maxim on 2/23/19.
//

#include <fcntl.h>
#include "sockets.h"
#include "messageTypes.h"
#include "metadata.h"
#include "../../../lib/netconf.h"

network_handler *handlers[MAX_HANDLERS];
int handlersCount = 0;

r_info socketCreate(char *_addr, char *port) {
    /*
     * We use connect() for UDP packet's to increase performance
     * This function returns new socket fd
     */
    addrinfo_t hints, *servinfo, *p;

    r_info res;

    int rv;
    int sockfd;

    // look up for an remote address and open a socket
    memset(&hints, 0, sizeof hints);
    // using ipv4
    hints.ai_family = AF_INET;
    // using UDP protocol
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo(_addr, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "Remote address lookup error: %s\n", gai_strerror(rv));
        exit(1);
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("Socket creation attempt failed");
            continue;
        }

        int yes = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        break;
    }

    if (p == NULL) {
        perror("Failed to create socket");
        exit(1);
    }

    // output buffer
    char output_buf[256];

    printf("Connected to local %s:%s\n",
           inet_ntop(p->ai_family, (sockaddr_in_t *) p->ai_addr, output_buf, sizeof(output_buf)), port);
    res.addr = *p->ai_addr;
    res.sockfd = sockfd;
    // addr no longer needed
    freeaddrinfo(servinfo);
    // setting socket to non-blocking
    fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL) | O_NONBLOCK);

    return res;
}

int socketWrite(r_info serv_info, uint8_t *data, size_t *len) {
    size_t total = 0;
    ssize_t n = -1;
    size_t left = *len;

    while (total < *len) {
        n = sendto(serv_info.sockfd, data + total, left, 0, &serv_info.addr, sizeof (serv_info.addr));
        if (n == -1) break;
        total += n;
        left -= n;
    }
    // in case of error, we will know how many bytes were really sent
    *len = total;

    return n == -1 ? -1 : 0;
}

int socketRead(int socketfd, uint8_t *res, size_t reslen) {
    ssize_t numbytes;
    // looking for data
    // actually recv - the same recvfrom but with no remote address needed
    if ((numbytes = recv(socketfd, res, reslen, 0)) <= 0) {
        if (numbytes == 0) {
            perror("connection closed");
            exit(1);
            close(socketfd);
            //return 0
        } else if (errno == EWOULDBLOCK) {
            printf("No data\n");
            return -1;
        }
    } else {
        printf("Got info!");
        return 1;
    }
}

int socketClose(int sockfd) {
    return close(sockfd);
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
