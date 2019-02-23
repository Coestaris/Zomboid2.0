//
// Created by maxim on 2/23/19.
//

#include "baseHandlers.h"

void handler_connected(socket_client* client, char* data, size_t dataLen)
{
    clientSendMessage(client, MSGTYPE_INIT_REQ, NULL, 0);
}

void handler_init_res(socket_client* client, char* data, size_t dataLen)
{
    if(!client->info->name) free(client->info->name);

    char* nstr = malloc((size_t)dataLen + 1);
    memcpy(nstr, data, (size_t)dataLen);
    nstr[dataLen] = '\0';

    client->info->name = nstr;

    printf("Thanks for initing! Your name is %s", client->info->name);
    clientSend(client, client->info->name, strlen(client->info->name));
}

void initBaseHandlers(void)
{
    pushHandler(MSGTYPE__CONNECTED, handler_connected);
    pushHandler(MSGTYPE_INIT_RES,   handler_init_res);
}
