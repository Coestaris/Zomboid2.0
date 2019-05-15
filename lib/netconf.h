//
// Created by h0tw4t3r on 5/1/19.
//

#ifndef SERVER_NETCONF_H
#define SERVER_NETCONF_H

#define MAX_BUFFER 1024
#define DATA_LENGTH 24
#define DISCONNECT_TIMEOUT 15
#define MONITORING_TIMEOUT 5
#define DEFAULT_PORT 25565

#include <inttypes.h>

typedef struct sockaddr sockaddr_t;
typedef struct sockaddr_in sockaddr_in_t;
typedef struct addrinfo addrinfo_t;
typedef struct timeval timeval_t;
typedef struct sockaddr_storage sockaddr_storage_t;
typedef struct in_addr in_addr_tt;
typedef uint8_t zsize_t;

#endif //SERVER_NETCONF_H
