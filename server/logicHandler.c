//
// Created by maxim on 2/23/19.
//

#include "logicHandler.h"

message_handler* handlers[MAX_HANDLERS];
int handlersCount = 0;
char send_buffer[BUFFER_SIZE + sizeof(int) + 1];

int handleConnection(socket_client* client)
{
    for(int handler = 0; handler < handlersCount; handler++) {
        if(handlers[handler]->messageType == MSGTYPE__CONNECTED) {
            handlers[handler]->func(client, NULL, 0);
        }
    }
}

int clientSend(socket_client* client, char* buffer, ssize_t buffLen)
{
    if(send(client->sd , buffer, (size_t)buffLen, 0) != buffLen)
    {
        perror("send");
        return 0;
    }
    else
    {
        return 1;
    }
}

int clientDisconnect(socket_client* client)
{
    if(close(client->sd) != -1) {

        client->sd = 0;
        client->buffLen = 0;
        client->info->state = STATE_EMPTY;

        memset(client->buffer, 0, BUFFER_SIZE);

        notifierSocketClosed(client);
        return 1;
    }
    else
    {
        perror("close");
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

void handleClients(socket_client** clients)
{
    for(int i = 0; i < MAX_CLIENTS; i++)
    {
        socket_client* client = clients[i];
        if(clientActive(client))
        {
            if(clientRecData(client))
            {
                if(client->buffLen < sizeof(int)) {
                    perror("Input message too short!");
                    continue;
                }

                int type;
                memcpy(&type, client->buffer, sizeof(int));

                //printf("Received message: type: %i, dataLen: %li\n", type, client->buffLen - sizeof(int));

                for(int handler = 0; handler < handlersCount; handler++) {
                    if(handlers[handler]->messageType == type || handlers[handler]->messageType == MSGTYPE__ANY) {
                        handlers[handler]->func(client, client->buffer + sizeof(int), client->buffLen - sizeof(int));
                    }
                }

                client->buffLen = 0;
            }
        }
    }
}

void clientSendMessage(socket_client* client, int messageType, char* buffer, ssize_t buffLen)
{
    memcpy(send_buffer, &messageType, sizeof(int));
    if(buffer) memcpy(send_buffer + sizeof(int), buffer, (size_t)buffLen);
    clientSend(client, send_buffer, (size_t)buffLen + sizeof(int));
}

void pushHandler(int messageType, void (*func)(socket_client*, char*, size_t))
{
    message_handler* mh = malloc(sizeof(message_handler));
    mh->func = func;
    mh->messageType = messageType;
    handlers[handlersCount++] = mh;
}