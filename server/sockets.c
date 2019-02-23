//
// Created by maxim on 2/23/19.
//

#include "sockets.h"
#include "actionNotifier.h"

uint16_t port = 1234;
socket_client* clients[MAX_CLIENTS];

void setPort(uint16_t _port)
{
    port = _port;
}

int socketInit(void)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i] = createClient();
    }

    notifierSocketInited();
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
        return 0;
    }

    if(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        return 0;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( (uint16_t) port );

    if(bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    notifierSocketListening(port);

    if (listen(master_socket, PENDING_CONNECTIONS) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    notifierSocketWaiting();
    addrlen = sizeof(address);

    while(1)
    {
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        for (i = 0; i < MAX_CLIENTS; i++)
        {
            sd = clients[i]->sd;
            if(sd > 0) FD_SET(sd, &readfds);
            if(sd > max_sd) max_sd = sd;
        }


        activity = select(max_sd + 1 , &readfds , NULL , NULL , NULL);
        if((activity < 0) && (errno != EINTR))
        {
            perror("select error");
            //return 0;
        }

        if(FD_ISSET(master_socket, &readfds))
        {
            if((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                return 0;
            }

            notifierSocketNew(new_socket, address);

            for(i = 0; i < MAX_CLIENTS; i++)
            {
                if( clients[i]->sd == 0 )
                {
                    clients[i]->sd = new_socket;
                    clients[i]->info->state = STATE_UNDEFINED;

                    notifierSocketAdded(i);
                    handleConnection(clients[i]);
                    break;
                }
            }
        }

        for (i = 0; i < MAX_CLIENTS; i++)
        {
            sd = clients[i]->sd;
            if (FD_ISSET( sd , &readfds))
            {
                if ((valread = read(sd , clients[i]->buffer, BUFFER_SIZE)) == 0)
                {
                    clientDisconnect(clients[i]);
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