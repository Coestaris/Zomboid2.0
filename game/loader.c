//
// Created by maxim on 1/24/19.
//

#include "loader.h"

void initScenes(void)
{
    gameScene* mainScene = createScene(SCENEID_MAIN, 0);
    mainScene->backgroundTexId = TEXID_BACK_CONCRETE;

    gameObject* player = createPlayer();
    scmAddStartupObject(mainScene, player);

    scmAddStartupObject(mainScene, createLightTracer(player));
    scmAddStartupObject(mainScene, createBox(100, 100));
    scmAddStartupObject(mainScene, createBox(300, 100));
    scmAddStartupObject(mainScene, createBox(350, 400));

    scmPushScene(mainScene);
}