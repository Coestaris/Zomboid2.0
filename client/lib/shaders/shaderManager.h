//
// Created by maxim on 4/29/19.
//
#ifndef ZOMBOID2_SHADERMANAGER_H
#define ZOMBOID2_SHADERMANAGER_H

#include <assert.h>

#include "shader.h"

#define SHADER_IMAGE 0

#define SHM_MAX_SHADERS 256

typedef struct {
    shader* shader;
    int id;

} shmNode;

uint8_t shmHasShader(int id);
void shmPushBuiltInShaders();
void shmPush(shader* shader, int id);
void shmInit();
shader* shmGetShader(int id);

#endif //ZOMBOID2_SHADERMANAGER_H
