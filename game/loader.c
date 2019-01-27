//
// Created by maxim on 1/24/19.
//

#include "loader.h"

void loadTextures(void)
{
    puts("Loading textures....");
    loadAnimation(3, TEXID_PLAYER, TEXSCOPE_MAIN, 15, 0,
         "../resources/images/player_1/image0.png",
         "../resources/images/player_1/image1.png",
         "../resources/images/player_1/image2.png");

    loadTexture("../resources/images/bullet.png", TEXID_BULLET, TEXSCOPE_MAIN, 0, 0, TEXMODE_DEFAULT);
    loadTexture("../resources/images/box.png", TEXID_BOX, TEXSCOPE_MAIN, 0, 0, TEXMODE_DEFAULT);

    loadTexture("../resources/images/light/simpleLight.png", TEXID_SIMPLE_LIGHT, TEXSCOPE_MAIN, 0, 0, TEXMODE_OVERLAY);
    loadTexture("../resources/images/light/light.png", TEXID_LIGHT, TEXSCOPE_MAIN, 0, 0, TEXMODE_OVERLAY);
    loadTexture("../resources/images/light/flashlight.png", TEXID_FLASHLIGHT, TEXSCOPE_MAIN, 110, 0, TEXMODE_OVERLAY);

    loadAnimation(6, TEXID_SHELLCASE, TEXSCOPE_MAIN, 0, 0,
            "../resources/images/shellCase/shellCase1.png",
            "../resources/images/shellCase/shellCase2.png",
            "../resources/images/shellCase/shellCase3.png",
            "../resources/images/shellCase/shellCase4.png",
            "../resources/images/shellCase/shellCase5.png",
            "../resources/images/shellCase/shellCase6.png");

    loadTexture("../resources/images/backgrounds/concrete.png", TEXID_BACK_CONCRETE, TEXSCOPE_MAIN, 0, 0, TEXMODE_BACKGROUND);

    puts("Loading textures done!");
}

void initScenes(void)
{
    gameScene* mainScene = createScene(SCENEID_MAIN, 0);
    mainScene->backgroundTexId = TEXID_BACK_CONCRETE;

    gameObject* player = createPlayer();
    scmAddStartupObject(mainScene, player);

    scmAddStartupObject(mainScene, createBox(100, 100));
    scmAddStartupObject(mainScene, createBox(300, 100));
    scmAddStartupObject(mainScene, createBox(350, 400));

    scmPushScene(mainScene);
}