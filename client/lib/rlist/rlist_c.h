//
// Created by maxim on 1/31/19.
//

#ifndef ZOMBOID2_RLIST_C_H
#define ZOMBOID2_RLIST_C_H

#include <malloc.h>

#define ARGC_VARIADIC -1

struct _rlist_c;

typedef struct _rlist_cdata {
    struct _rlist_c* command;

    char** args;

    char* fnToAddLines;
    int strict;

    int lineIndex;
    char* filename;

} rlist_cdata_t;

typedef struct _rlist_c {
    const char* name;
    int argumentCount;

    int (*runFunc)(rlist_cdata_t* arguments);
} rlist_c_t;

rlist_c_t* create_command(const char* name, int argCount, int (*runFunc)(rlist_cdata_t* arguments));

#endif //ZOMBOID2_RLIST_C_H
