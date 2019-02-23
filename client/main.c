//#include "game/game.h"

#include "sockets.h"

void handler_init_res(char* data, size_t len)
{
    socketsSendMessage(MSGTYPE_INIT_RES, "Coestaris", sizeof("coestaris"));
}

int main(int argc, char** argv)
{
    //initGame(argc, argv);
    //runGame();

    pushHandler(MSGTYPE_INIT_REQ, handler_init_res);

    int status = socketsOpen();
    if(status == -2)
    {
        puts("Server is down =c");
        return -1;
    }
    else if(status == -1)
    {
        puts("Unable to connect =c");
        return -1;
    }

    while(1)
    {
        socketsGetUpdates();
    }

    return 0;
}