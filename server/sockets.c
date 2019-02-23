//
// Created by maxim on 2/23/19.
//

#include "sockets.h"

uint16_t port = 1234;
socket_client* clients[MAX_CLIENTS];

void setPort(uint16_t _port)
{
    port = _port;
}

int socketInit(void)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i] = malloc(sizeof(socket_client));
        clients[i]->sd = 0;
    }

    return 1;
}

int socketMainloop(void)
{
    int opt = 1;
    int master_socket , addrlen , new_socket , activity, i, sd;
    ssize_t valread;
    int max_sd;
    struct sockaddr_in address;

    fd_set readfds;

    if((master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( (uint16_t) port );

    if(bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Listener on port %d \n", port);

    if (listen(master_socket, PENDING_CONNECTIONS) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while(1)
    {
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        for (i = 0 ; i < MAX_CLIENTS ; i++)
        {
            sd = clients[i]->sd;
            if(sd > 0) FD_SET(sd , &readfds);
            if(sd > max_sd) max_sd = sd;
        }


        activity = select(max_sd + 1 , &readfds , NULL , NULL , NULL);
        if((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }

        if (FD_ISSET(master_socket, &readfds))
        {
            if((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket,
                    inet_ntoa(address.sin_addr) , ntohs(address.sin_port));


            for(i = 0; i < MAX_CLIENTS; i++)
            {
                if( clients[i]->sd == 0 )
                {
                    clients[i]->sd = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);
                    break;
                }
            }
        }

        for (i = 0; i < MAX_CLIENTS; i++)
        {
            sd = clients[i]->sd;
            if (FD_ISSET( sd , &readfds))
            {
                if ((valread = read(sd , clients[i]->buffer, 1024)) == 0)
                {
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                    close( sd );
                    clients[i]->sd = 0;
                }
                else
                {
                    clients[i]->buffLen = valread;
                }
            }
        }

        handleClients(clients);
    }
}