//
// Created by maxim on 1/31/19.
//

#include "rlist_commands.h"

rlist_c* commands[MAX_COMMANDS_COUNT];
rlist_variable* variables[MAX_VARIABLES_COUNT];
int variablesCount = 0;
int commandsCount = 0;

void rlist_register_command(rlist_c* command)
{
    commands[commandsCount++] = command;
}

void initCommands(void)
{
    rlist_register_command(create_command("echo", 1, rlist_command_echo));
    rlist_register_command(create_command("echo_v", 1, rlist_command_echo_v));
    rlist_register_command(create_command("echo_all_vars", 0, rlist_command_echo_all_vars));

    rlist_register_command(create_command("set", 2, rlist_command_set));
    rlist_register_command(create_command("inc", 1, rlist_command_inc));
}

int rlist_command_echo_v(rlist_cdata *data)
{
    for(int i = 0; i < variablesCount; i++) {
        if(!strcmp(data->args[0], variables[i]->name)) {
            printf("Rlist: Value of \"%s\" is \"%s\"\n", data->args[0], variables[i]->value);
            return true;
        }
    }

    printf("Rlist: Unable to find variable \"%s\"\n", data->args[0]);
    return true;
}

int rlist_command_echo_all_vars(rlist_cdata *data)
{
    if(variablesCount == 0) {
        printf("Rlist: No variables registered\n");
    } else {
        printf("Rlist: Registered %i variables: \n", variablesCount);
        for(int i = 0; i < variablesCount; i++) {
            printf("  - %15s set as \"%s\"\n", variables[i]->name, variables[i]->value);
        }
    }
    return true;
}

int rlist_command_inc(rlist_cdata* data)
{
    if(!fileExists(data->args[0])) {
        printf("Rlist error: Unable to reach specified include file \"%s\"", data->args[0]);
        if(data->strict) return false;
        else return true;
    }

    data->addLinesArgIndex = 0;
    return true;
}

int rlist_command_set(rlist_cdata *data)
{
    rlist_variable* var = malloc(sizeof(rlist_variable));

    for(int i = 0; i < variablesCount; i++)
        if(!strcmp(data->args[0], variables[i]->name)) {
            printf("Rlist: Variable with same name already exists");
            return !data->strict;
        }

    var->name  = malloc(strlen(data->args[0]) + 1);
    var->value = malloc(strlen(data->args[1]) + 1);

    strcpy(var->name,  data->args[0]);
    strcpy(var->value, data->args[1]);

    variables[variablesCount++] = var;

    return true;
}

int rlist_command_echo(rlist_cdata *data)
{
    printf("Rlist: %s\n", data->args[0]);
    return true;
}

rlist_c **rlist_getcommands(int *count)
{
    *count = commandsCount;
    return commands;
}
