//
// Created by maxim on 1/31/19.
//

#ifndef ZOMBOID2_RLIST_COMMANDS_H
#define ZOMBOID2_RLIST_COMMANDS_H

#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <libgen.h>
#include <zconf.h>

#include "../resources/texManager.h"
#include "../gameLogic/gameScene.h"
#include "../helpers.h"
#include "rlist_c.h"

#define MAX_COMMANDS_COUNT 100
#define MAX_VARIABLES_COUNT 100

typedef struct _rlist_variable
{
    char* name;
    char* value;

} rlist_variable_t;

void rlist_register_command(rlist_c_t* command);
int rlist_command_set(rlist_cdata_t* data);
int rlist_command_inc(rlist_cdata_t* data);
int rlist_command_echo(rlist_cdata_t* data);
int rlist_command_echo_v(rlist_cdata_t* data);
int rlist_command_echo_all_vars(rlist_cdata_t* data);
int rlist_command_image(rlist_cdata_t* data);
int rlist_command_animation(rlist_cdata_t* data);
int rlist_command_scene(rlist_cdata_t* data);
int rlist_command_sog_open(rlist_cdata_t* data);
int rlist_command_sog_add(rlist_cdata_t* data);
int rlist_command_sog_add_ex(rlist_cdata_t* data);
int rlist_command_scm_close(rlist_cdata_t* data);
int rlist_command_scm_sc_load(rlist_cdata_t* data);
int rlist_command_scm_sc_unload(rlist_cdata_t* data);
int rlist_command_scm_objects_destroy(rlist_cdata_t* data);
int rlist_command_scm_objects_free(rlist_cdata_t* data);
int rlist_command_scm_ltracer(rlist_cdata_t* data);

void initCommands(void);

rlist_c_t** rlist_getcommands(int* count);

#endif //ZOMBOID2_RLIST_COMMANDS_H
