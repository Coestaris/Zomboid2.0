//
// Created by maxim on 2/23/19.
//

#include "sockets.h"
#include "messageTypes.h"

char* addr = "127.0.0.1";
uint16_t port = 1234;

int fd = 0;

ssize_t buffLen = 0;
char buffer[BUFFER_SIZE];
char send_buffer[BUFFER_SIZE + sizeof(int) + 1];

network_handler* handlers[MAX_HANDLERS];
int handlersCount = 0;

void socketsSetAddress(char* _addr)
{
    addr = _addr;
}

void socketsSetPort(uint16_t _port)
{
    port = _port;
}

int socketsOpen(void)
{
    struct sockaddr_in serv_addr;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, addr, &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if(connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -2;
    }

    return 0;
}

int socketsGetUpdates(void)
{
    buffLen = read(fd, buffer, BUFFER_SIZE);
    if(buffLen < 0) {
        return 0;
    }

    if(buffLen != 0) {

        if(buffLen < 4) {
            perror("message is too short!");
            return 1;
        }

        int type;
        memcpy(&type, buffer, sizeof(int));

        printf("Got message with type: %i, dataLen: %li\n", type, buffLen);

        for(int i = 0; i < handlersCount; i++) {
            if(handlers[i]->messageType == type || handlers[i]->messageType == MSGTYPE__ANY) {
                handlers[i]->func(buffer + sizeof(int), buffLen - sizeof(int));
            }
        }
    }

    return 1;
}

void pushHandler(int messageType, void (*func)(char*, size_t))
{
    network_handler* nh = malloc(sizeof(network_handler));
    nh->messageType = messageType;
    nh->func = func;
    handlers[handlersCount++] = nh;
}

int socketsSend(char* buffer, size_t buffLen)
{
    if(send(fd, buffer, buffLen, 0) != buffLen) {
        perror("Send!");
        return 0;
    } else {
        return 1;
    }
}

int socketsSendMessage(int messageType, char* buffer, size_t buffLen)
{
    memcpy(send_buffer, &messageType, sizeof(int));
    if(buffer) memcpy(send_buffer + sizeof(int), buffer, (size_t)buffLen);
    return socketsSend(send_buffer, (size_t)buffLen + sizeof(int));
}
