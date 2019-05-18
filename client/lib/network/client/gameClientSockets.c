//
// Created by maxim on 2/23/19.
//

#include "gameClientSockets.h"

network_handler *handlers[MAX_HANDLERS];
int handlersCount = 0;

r_info gameSocketCreate(char *_addr, char *port) {
    /*
     * We use connect() for UDP packet's to increase performance
     * This function returns new socket fd
     */
    addrinfo_t hints, *servinfo, *p;

    r_info res;

    int rv;
    int sockfd = -1;

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

int gameSocketWrite(r_info serv_info, uint8_t *data, size_t *len) {
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

int gameSocketRead(int socketfd, uint8_t *res, size_t reslen) {
    ssize_t numbytes;
    // looking for data
    // actually recv - the same recvfrom but with no remote address needed
    if ((numbytes = recv(socketfd, res, reslen, 0)) <= 0) {
        if (numbytes == 0) {
            perror("connection closed");
            close(socketfd);
            exit(1);
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

int gameSocketHandlerSubscribe(network_handler *handler) {
    if (handlersCount == MAX_HANDLERS) {
        return -1;
    }
    handlers[handler->messageType] = handler;
    handlersCount++;
    return handlersCount;
}

network_handler * gameSocketHandlerCreate(int messageType, void (*func)(char*, size_t)) {
    network_handler *newHandler = malloc(sizeof (network_handler));
    newHandler->messageType = messageType;
    newHandler->func = func;
    return newHandler;
}

void gameSocketHandlersClear() {
    for (int i = 0; i < handlersCount; i++) free(handlers[i]);
}

int gameSocketClose(int sockfd) {
    return close(sockfd);
}
