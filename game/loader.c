//
// Created by maxim on 1/24/19.
//

#include "loader.h"

void loadTexture(const char* fn, int id, int scope)
{
    if(fileExists(fn))
    {
        texmPush(createTex(fn, id, scope, 0, 0));
    }
    else
    {
        printf("Unable to reach file \"%s\"", fn);
        exit(1);
    }
}


void loadTextures(void)
{
    texmPush(createAnimation(3, TEXID_PLAYER, 15, 0, TEXSCOPE_MAIN,
         "../resources/images/player_1/image0.png",
         "../resources/images/player_1/image1.png",
         "../resources/images/player_1/image2.png"));

    loadTexture("../resources/images/bullet.png", TEXID_BULLET, TEXSCOPE_MAIN);
}

void initScenes(void)
{
    gameScene* mainScene = createScene(SCENEID_MAIN, 0);
    addStarupObject(mainScene, createPlayer());

    pushScene(mainScene);
}