//
// Created by maxim on 2/23/19.
//

#include "../lib/client.h"

socket_client* createClient(void)
{
    socket_client* client = malloc(sizeof(socket_client));
    client->info = malloc(sizeof(client_info));

    client->sd = 0;
    client->buffLen = 0;

    client->info->state = STATE_EMPTY;
    client->info->name = NULL;

    memset(client->buffer, 0, BUFFER_SIZE);

    return client;
}