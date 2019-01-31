//
// Created by maxim on 1/31/19.
//

#include "rlist_commands.h"

rlist_c* commands[MAX_COMMANDS_COUNT];
int commandsCount = 0;

void rlist_register_command(rlist_c* command)
{
    commands[commandsCount++] = command;
}

void initCommands(void)
{
    rlist_register_command(create_command("echo", 1, rlist_command_echo));
    rlist_register_command(create_command("set", 2, rlist_command_set));
}

void rlist_command_set(rlist_cdata *data)
{
    printf("setting %s as %s\n", data->args[0], data->args[1]);
}

void rlist_command_echo(rlist_cdata *data)
{
    printf("Rlist: %s\n", data->args[0]);
}

rlist_c **rlist_getcommands(int *count)
{
    *count = commandsCount;
    return commands;
}
