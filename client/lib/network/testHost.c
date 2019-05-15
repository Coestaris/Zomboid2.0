#include "../../../server/lib/network/sockets.h"
#include "../../../lib/idtp.h"

int main(int argc, char** argv) {
    int sockfd = idServerSocketCreate("25565");
    idServerSocketMainLoop(sockfd);
    return 0;
}