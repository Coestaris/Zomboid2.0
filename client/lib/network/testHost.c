#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "host/sockets.h"
#include "../../../server/handlers/baseHandlers.h"

int main(int argc, char** argv) {
    int listener = socketServerCreate("9305");
    socketMainloop(listener);
    return 0;
}