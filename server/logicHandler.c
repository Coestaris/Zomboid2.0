//
// Created by maxim on 2/23/19.
//

#include "logicHandler.h"

void handleClients(socket_client** clients)
{
    for(int i = 0; i < MAX_CLIENTS; i++)
    {
        socket_client* client = clients[i];
        if(clientActive(client))
        {
            if(clientRecData(client))
            {
                client->buffer[client->buffLen] = '\0';

                if(client->buffer[0] == 'c')
                {
                    clientDisconnect(client);
                }
                else
                {
                    clientSend(client, client->buffer, client->buffLen);
                }
            }
        }
    }
}