//
// Created by maxim on 2/23/19.
//

#include "actionNotifier.h"

void notifierSocketInited(void)
{
    puts("[Socket]: Sockets inited");
}

void notifierSocketListening(char * port)
{
    printf("[Socket]: Listener on port %s \n", port);
}

void notifierSocketWaiting(void)
{
    puts("[Socket]: Waiting for connections ...");
}

void notifierSocketNew(int socket, struct sockaddr_in addr)
{
    printf("[Socket][New connection]: socket_fd: %d, ip: %s, port: %d\n" , socket,
           inet_ntoa(addr.sin_addr) , ntohs(addr.sin_port));
}

void notifierSocketAdded(int index)
{
    printf("[Socket]: Adding to list of sockets as %d\n", index);
}

void notifierSocketClosed(socket_client* client)
{
    struct sockaddr_in address;
    int addrlen;

    getpeername(client->sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
    printf("[Socket][Host disconnected]: ip: %s, port: %d \n", inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

}