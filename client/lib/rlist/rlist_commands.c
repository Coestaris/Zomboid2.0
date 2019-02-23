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

    rlist_register_command(create_command("image", 6, rlist_command_image));
    rlist_register_command(create_command("animation", 7, rlist_command_animation));

    rlist_register_command(create_command("scene", 3, rlist_command_scene));
    rlist_register_command(create_command("sog_open", 1, rlist_command_sog_open));
    rlist_register_command(create_command("sog_add", 3, rlist_command_sog_add));
    rlist_register_command(create_command("sog_add_ex", 10, rlist_command_sog_add_ex));
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

char* getFilename(char* scriptFn, char* filename)
{
    char* ts1 = strdup(scriptFn);
    char* ts2 = strdup(filename);
    char* ts3 = strdup(filename);

    char* dir = dirname(ts1);
    char* dirDest = dirname(ts2);
    char* name = basename(ts3);

    char cwd[256];
    getcwd(cwd, 256);

    char* fullPath = malloc(256);
    memset(fullPath, 0, 256);

    if(dir[0] != '/') {
        fullPath = strcat(fullPath, cwd);
        fullPath = strcat(fullPath, "/");
    }

    fullPath = strcat(fullPath, dir);
    fullPath = strcat(fullPath, "/");
    if(strlen(dirDest) != 1 && dirDest[0] != '.') {
        fullPath = strcat(fullPath, dirDest);
        fullPath = strcat(fullPath, "/");
    }
    fullPath = strcat(fullPath, name);

    free(ts1);
    free(ts2);
    free(ts3);

    return fullPath;
}

int rlist_command_inc(rlist_cdata* data)
{
    char* filename = getFilename(data->filename, data->args[0]);

    if(!fileExists(filename)) {
        printf("Rlist error: Unable to reach specified include file \"%s\", at line %i in \"%s\"\n", filename, data->lineIndex, data->filename);

        free(filename);
        if(data->strict) return false;
        else return true;
    }

    data->fnToAddLines = filename;
    return true;
}

int rlist_command_set(rlist_cdata *data)
{
    rlist_variable* var = malloc(sizeof(rlist_variable));

    for(int i = 0; i < variablesCount; i++)
        if(!strcmp(data->args[0], variables[i]->name)) {
            printf("Rlist error: Variable with same name \"%s\" already exists, at line %i in \"%s\"\n", variables[i]->name, data->lineIndex, data->filename);
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

int isInt(char* string) {
    int start = 0;
    if(string[0] == '-') start = 1;
    for(int i = start; i < strlen(string); i++)
        if(!isdigit(string[i])) return false;

    return true;
}

int isDouble(const char *s, double *dest) {
    char *endptr;
    *dest = strtod(s, &endptr);
    if (s == endptr) {
        return false;
    }

    while (isspace((unsigned char ) *endptr))
        endptr++;

    return *endptr == '\0';
}

rlist_variable* getVar(char* name) {
    for(int i = 0; i < variablesCount; i++)
        if(!strcmp(variables[i]->name, name))
            return variables[i];
    return NULL;
}

int getDoubleValue(double * res, char* str, const char* pname, rlist_cdata *data)
{
    rlist_variable* var;

    if(!isDouble(str, res)) {
        if((var = getVar(str))) {
            if(!isDouble(var->value, res)) {
                printf("Rlist data error: specified variable for %s should be correct float-point number value, but got %s, at line %i in \"%s\"\n",
                       pname, var->value, data->lineIndex, data->filename);
                return false;
            }
        } else {

            printf("Rlist data error: %s should be correct float-point number value or variable name, but got \"%s\", at line %i in \"%s\"\n",
                   pname, str, data->lineIndex, data->filename);
            return false;
        }
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
int getIntValue(int* res, char* str, const char* pname, rlist_cdata *data)
{
    rlist_variable* var;

    if(isInt(str))
    {
        *res = atoi(str);
    }
    else if((var = getVar(str)))
    {

        if(!isInt(var->value)) {
            printf("Rlist data error: specified variable for %s should be correct integer value, but got %s, at line %i in \"%s\"\n",
                    pname, var->value, data->lineIndex, data->filename);
            return false;
        }
        *res = atoi(var->value);
    } else {
        printf("Rlist data error: %s should be correct integer value or variable name, but got \"%s\", at line %i in \"%s\"\n",
                pname, str, data->lineIndex, data->filename);
        return false;
    }

    return true;
}
#pragma clang diagnostic pop

int rlist_command_image(rlist_cdata *data) {

    int id, scope, mode;
    double cX, cY;
    char* path;

    if(!getIntValue   (&id,    data->args[0], "id",    data)) return !data->strict;
    if(!getIntValue   (&scope, data->args[1], "scope", data)) return !data->strict;
    if(!getDoubleValue(&cX,    data->args[2], "cX",    data)) return !data->strict;
    if(!getDoubleValue(&cY,    data->args[3], "cY",    data)) return !data->strict;
    if(!getIntValue   (&mode,  data->args[4], "mode",  data)) return !data->strict;
    path = getFilename(data->filename, data->args[5]);

    if(!fileExists(path)) {
        printf("Rlist data error: Specified image path \"%s\" is not exists, at line %i in \"%s\"\n", path, data->lineIndex, data->filename);
        return !data->strict;
    }

    texmPush(createTex(path, id, scope, vec(cX, cY), mode));
    return true;
}

int rlist_command_animation(rlist_cdata* data) {
    //; type      frameCnt    id                  scope                cX  cY    mode         paths
    int frameCnt, id, scope, mode;
    double cX, cY;
    char **paths;

    if (!getIntValue(&frameCnt, data->args[0], "frameCnt", data)) return !data->strict;
    if (!getIntValue(&id, data->args[1], "id", data)) return !data->strict;
    if (!getIntValue(&scope, data->args[2], "scope", data)) return !data->strict;
    if (!getDoubleValue(&cX, data->args[3], "cX", data)) return !data->strict;
    if (!getDoubleValue(&cY, data->args[4], "cY", data)) return !data->strict;
    if (!getIntValue(&mode, data->args[5], "mode", data)) return !data->strict;

    paths = malloc(frameCnt * sizeof(char*));
    size_t len = strlen(data->args[6]) + 5;

    for(int i = 0; i < frameCnt; i++)
    {
        char* tmp = malloc(len);
        memset(tmp, 0, len);

        snprintf(tmp, len, data->args[6], i);

        paths[i] = getFilename(data->filename, tmp);

        if(!fileExists(paths[i])) {
            printf("Rlist data error: Specified image path \"%s\" is not exists, at line %i in \"%s\"\n", paths[i], data->lineIndex, data->filename);
            return !data->strict;
        }

        free(tmp);
    }

    texmPush(createAnimation(paths, frameCnt, id, scope, vec(cX, cY), mode));
}

gameScene* listeningScene = NULL;

int rlist_command_scene(rlist_cdata *data)
{
    int id, scope, back;
    if (!getIntValue(&id, data->args[0], "id", data)) return !data->strict;
    if (!getIntValue(&scope, data->args[1], "scope", data)) return !data->strict;
    if (!getIntValue(&back, data->args[2], "back", data)) return !data->strict;

    gameScene* scene = createScene(id, scope);
    scene->backgroundTexId = back;

    scmPushScene(scene);
}

int rlist_command_sog_open(rlist_cdata *data)
{
    int id;
    if (!getIntValue(&id, data->args[0], "id", data)) return !data->strict;
    listeningScene = scmGetScene(id);
    if(listeningScene == NULL) {
        printf("Rlist data error: Unable to find scene with specified id \"%i\", at line %i in \"%s\"\n", id, data->lineIndex, data->filename);
        return !data->strict;
    }
}

int rlist_command_sog_add(rlist_cdata *data)
{
    if(listeningScene == NULL) {
        printf("Rlist data error: No scene is opened, at line %i in \"%s\"\n", data->lineIndex, data->filename);
        return !data->strict;
    }

    int id;
    double x, y;
    if (!getIntValue   (&id, data->args[0], "id", data)) return !data->strict;
    if (!getDoubleValue(&x,  data->args[1], "x",  data)) return !data->strict;
    if (!getDoubleValue(&y,  data->args[2], "y",  data)) return !data->strict;

    publicObject* po = scmGetPublicObject(id);
    if(po == NULL) {
        printf("Rlist data error: Unable to find public object with id %i, at line %i in \"%s\"\n", id, data->lineIndex, data->filename);
        return !data->strict;
    }

    gameObject* go = po->init();
    go->pos = vec(x, y);
    scmAddStartupObject(listeningScene, go);
}

int rlist_command_sog_add_ex(rlist_cdata *data)
{
    if(listeningScene == NULL) {
        printf("Rlist data error: No scene is opened, at line %i in \"%s\"\n", data->lineIndex, data->filename);
        return !data->strict;
    }

    int id, texId, _color, drawable, depth, ani_speed;
    double x, y, angle, size;
    if (!getIntValue   (&id,        data->args[0], "id",        data)) return !data->strict;
    if (!getDoubleValue(&x,         data->args[1], "x",         data)) return !data->strict;
    if (!getDoubleValue(&y,         data->args[2], "y",         data)) return !data->strict;

    publicObject* po = scmGetPublicObject(id);
    if(po == NULL) {
        printf("Rlist data error: Unable to find public object with id %i, at line %i in \"%s\"\n", id, data->lineIndex, data->filename);
        return !data->strict;
    }

    gameObject* go = po->init();
    go->pos = vec(x, y);

    const char* defaults = "defaults"; //TODO

    if(strcmp(data->args[3], defaults) != 0) {
        if (!getDoubleValue(&angle, data->args[3], "angle", data)) return !data->strict;
        go->angle = angle;
    }

    if(strcmp(data->args[4], defaults) != 0) {
        if (!getDoubleValue(&size, data->args[4], "size", data)) return !data->strict;
        go->size = size;
    }

    if(strcmp(data->args[5], defaults) != 0) {
        if (!getIntValue(&texId, data->args[5], "texid", data)) return !data->strict;
        go->texID = texId;
    }

    if(strcmp(data->args[6], defaults) != 0) {
        if (!getIntValue(&_color, data->args[6], "color", data)) return !data->strict;

    }

    if(strcmp(data->args[7], defaults) != 0) {
        if (!getIntValue(&drawable, data->args[7], "drawable", data)) return !data->strict;
        go->drawable = drawable;
    }

    if(strcmp(data->args[8], defaults) != 0) {
        if (!getIntValue(&depth, data->args[8], "depth", data)) return !data->strict;
        go->depth = depth;
    }

    if(strcmp(data->args[9], defaults) != 0) {
        if (!getIntValue(&ani_speed, data->args[9], "ani_speed", data)) return !data->strict;
        go->animationSpeed = ani_speed;
    }

    scmAddStartupObject(listeningScene, go);
}

//object_ex   scene_id           x     y     angle     size        texid       color      drawable   depth      ani_speed