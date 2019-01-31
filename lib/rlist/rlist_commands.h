//
// Created by maxim on 1/31/19.
//

#ifndef ZOMBOID2_RLIST_COMMANDS_H
#define ZOMBOID2_RLIST_COMMANDS_H

#include "rlist_c.h"

#define MAX_COMMANDS_COUNT 100

void rlist_register_command(rlist_c* command);

void rlist_command_set (rlist_cdata* data);
void rlist_command_echo(rlist_cdata* data);

void initCommands(void);
rlist_c** rlist_getcommands(int* count);

#endif //ZOMBOID2_RLIST_COMMANDS_H
