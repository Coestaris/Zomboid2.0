//
// Created by maxim on 2/23/19.
//

#include "client.h"

int clientSend(socket_client* client, char* buffer, ssize_t buffLen)
{
    return send(client->sd , buffer, (size_t)buffLen, 0) == buffLen;
}

int clientDisconnect(socket_client* client)
{
    struct sockaddr_in address;
    int addrlen;

    getpeername(client->sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
    printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

    if(close(client->sd) != -1) {
        client->sd = 0;
        return 1;
    } else {
        return 0;
    }
}

int clientActive(socket_client* client)
{
    return client->sd != 0;
}

int clientRecData(socket_client* client)
{
    return client->buffLen != 0;
}