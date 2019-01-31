//
// Created by maxim on 1/31/19.
//

#ifndef ZOMBOID2_RLIST_C_H
#define ZOMBOID2_RLIST_C_H

#include <malloc.h>

#define ARGC_VARIADIC -1

struct rlist_c;

typedef struct rlist_cdata {
    struct rlist_c* command;

    char** args;

    char* currentDir;
    int addLinesArgIndex;
    int strict;

} rlist_cdata;

typedef struct rlist_c {
    const char* name;
    int argumentCount;

    int (*runFunc)(rlist_cdata* arguments);
} rlist_c;

rlist_c* create_command(const char* name, int argCount, int (*runFunc)(rlist_cdata* arguments));

#endif //ZOMBOID2_RLIST_C_H
