//
// Created by maxim on 1/31/19.
//

#include "rlist_c.h"

rlist_c* create_command(const char* name, int argCount, int (*runFunc)(rlist_cdata* arguments))
{
    rlist_c* command = malloc(sizeof(rlist_c));
    command->name = name;
    command->argumentCount = argCount;
    command->runFunc = runFunc;
    return command;
}