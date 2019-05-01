#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "lib/network/sockets.h"
#include "handlers/baseHandlers.h"

int isInt(char* string) {
    int start = 0;
    if(string[0] == '-') start = 1;
    for(int i = start; i < strlen(string); i++)
        if(!isdigit(string[i])) return false;

    return true;
}

int main(int argc, char** argv) {
    int listener = socketServerCreate("9305");
    socketMainloop(listener);
    return 0;
}