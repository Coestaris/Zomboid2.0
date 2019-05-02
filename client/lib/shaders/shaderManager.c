//
// Created by maxim on 4/29/19.
//

#include "shaderManager.h"

shmNode_t* nodes[SHM_MAX_SHADERS];
size_t nodeCount;

uint8_t shmHasShader(int id)
{
    for(size_t i = 0; i < nodeCount; i++)
        if(nodes[i]->id == id) return 1;
    return 0;
}

void shmPush(shader_t* shader, int id)
{
    assert(shader != NULL);
    assert(!shmHasShader(id));

    nodes[nodeCount]->shader = shader;
    nodes[nodeCount++]->id = id;
}

void shmPushBuiltInShaders()
{
    //shmPush(shaderCreate("shaders/image.vsh", "shaders/image.fsh"), SHADER_IMAGE);
    //shmPush(shaderCreate("shaders/background.vsh", "shaders/background.fsh"), SHADER_BACKGROUND);
}

void shmInit()
{
    for(size_t i = 0; i < SHM_MAX_SHADERS; i++)
    {
        nodes[i] = malloc(sizeof(shmNode_t));
        nodes[i]->shader = NULL;
        nodes[i]->id = -1;
    }
}

shader_t* shmGetShader(int id)
{
    for(size_t i = 0; i < nodeCount; i++)
        if(nodes[i]->id == id) return nodes[i]->shader;
    return NULL;
}