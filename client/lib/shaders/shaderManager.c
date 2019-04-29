//
// Created by maxim on 4/29/19.
//

#include "shaderManager.h"

shmNode* nodes[SHM_MAX_SHADERS];
size_t nodeCount;

uint8_t shmHasShader(int id)
{
    for(size_t i = 0; i < nodeCount; i++)
        if(nodes[i]->id == id) return 1;
    return 0;
}

void shmPush(shader* shader, int id)
{
    assert(shader != NULL);
    assert(!shmHasShader(id));

    nodes[nodeCount]->shader = shader;
    nodes[nodeCount++]->id = id;
}

void shmPushBuiltInShaders()
{
    shmPush(shaderCreate("shaders/image.vsh", "shaders/image.fsh"), SHADER_IMAGE);
}

void shmInit()
{
    for(size_t i = 0; i < SHM_MAX_SHADERS; i++)
    {
        nodes[i] = malloc(sizeof(shmNode));
        nodes[i]->shader = NULL;
        nodes[i]->id = -1;
    }
}

shader* shmGetShader(int id)
{
    for(size_t i = 0; i < nodeCount; i++)
        if(nodes[i]->id == id) return nodes[i]->shader;
    return NULL;
}