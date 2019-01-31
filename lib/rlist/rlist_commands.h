//
// Created by maxim on 1/31/19.
//

#ifndef ZOMBOID2_RLIST_COMMANDS_H
#define ZOMBOID2_RLIST_COMMANDS_H

#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>

#include "../texManager.h"
#include "../helpers.h"
#include "rlist_c.h"

#define MAX_COMMANDS_COUNT 100
#define MAX_VARIABLES_COUNT 100

typedef struct rlist_variable {
    char* name;
    char* value;

} rlist_variable;

void rlist_register_command(rlist_c* command);

int rlist_command_set(rlist_cdata* data);
int rlist_command_inc(rlist_cdata* data);
int rlist_command_echo(rlist_cdata* data);
int rlist_command_echo_v(rlist_cdata *data);
int rlist_command_echo_all_vars(rlist_cdata *data);
int rlist_command_image(rlist_cdata* data);
int rlist_command_animation(rlist_cdata* data);

void initCommands(void);
rlist_c** rlist_getcommands(int* count);

#endif //ZOMBOID2_RLIST_COMMANDS_H
