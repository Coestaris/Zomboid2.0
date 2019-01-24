//
// Created by maxim on 1/24/19.
//

#include "loader.h"

void loadTexture(const char* fn, int id, int scope)
{
    if(fileExists(fn))
    {
        texmPush(createTex(fn, id, scope));
    }
    else
    {
        printf("Unable to reach file \"%s\"", fn);
        exit(1);
    }
}


void loadTextures(void)
{
    loadTexture("in.png",  TEXID_PLAYER, TEXSCOPE_MAIN);
    loadTexture("in1.png", TEXID_BULLET, TEXSCOPE_MAIN);
    loadTexture("in2.png", 3, TEXSCOPE_MAIN);
}

void initScenes(void)
{
    gameScene* mainScene = createScene(SCENEID_MAIN, 0);
    addStarupObject(mainScene, createPlayer());

    pushScene(mainScene);
}