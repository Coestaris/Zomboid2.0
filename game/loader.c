//
// Created by maxim on 1/24/19.
//

#include "loader.h"

void loadTextures(void)
{
    loadAnimation(3, TEXID_PLAYER, TEXSCOPE_MAIN, 15, 0,
         "../resources/images/player_1/image0.png",
         "../resources/images/player_1/image1.png",
         "../resources/images/player_1/image2.png");

    loadTexture("../resources/images/bullet.png", TEXID_BULLET, TEXSCOPE_MAIN, 0, 0, false);
    loadTexture("../resources/images/box.png", TEXID_BOX, TEXSCOPE_MAIN, 0, 0, false);

    loadTexture("../resources/images/backgrounds/concrete.png", TEXID_BACK_CONCRETE, TEXSCOPE_MAIN, 0, 0, true);
}

void initScenes(void)
{
    gameScene* mainScene = createScene(SCENEID_MAIN, 0);
    mainScene->backgroundTexId = TEXID_BACK_CONCRETE;

    addStarupObject(mainScene, createPlayer());
    addStarupObject(mainScene, createBox(100, 100));
    addStarupObject(mainScene, createBox(300, 100));
    addStarupObject(mainScene, createBox(350, 400));

    pushScene(mainScene);
}