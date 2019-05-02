//
// Created by maxim on 1/31/19.
//

#include "rlist_c.h"

rlist_c_t* create_command(const char* name, int argCount, int (*runFunc)(rlist_cdata_t* arguments))
{
    rlist_c_t* command = malloc(sizeof(rlist_c_t));
    command->name = name;
    command->argumentCount = argCount;
    command->runFunc = runFunc;
    return command;
}