#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "sockets.h"

int isInt(char* string) {
    int start = 0;
    if(string[0] == '-') start = 1;
    for(int i = start; i < strlen(string); i++)
        if(!isdigit(string[i])) return false;

    return true;
}

int main(int argc, char** argv) {

    if(argc != 1) {
        if(!isInt(argv[1])) {
            perror("parsing port");
        }

        setPort(atoi(argv[1]));
    }

    socketInit();
    socketMainloop();

    return 0;
}