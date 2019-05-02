//
// Created by maxim on 4/29/19.
//
#ifndef ZOMBOID2_SHADERMANAGER_H
#define ZOMBOID2_SHADERMANAGER_H

#include <assert.h>

#include "shader.h"

#define SHADER_IMAGE 0
#define SHADER_BACKGROUND 1

#define SHM_MAX_SHADERS 256

typedef struct {
    shader_t* shader;
    int id;

} shmNode_t;

uint8_t shmHasShader(int id);
void shmPushBuiltInShaders();
void shmPush(shader_t* shader, int id);
void shmInit();
shader_t* shmGetShader(int id);

#endif //ZOMBOID2_SHADERMANAGER_H
