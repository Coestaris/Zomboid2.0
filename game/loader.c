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
    scmAddStartupObject(mainScene, createBox(200, 100));
    scmAddStartupObject(mainScene, createBox(300, 100));
    scmAddStartupObject(mainScene, createBox(400, 100));


    scmAddStartupObject(mainScene, createBox(160, 230));
    scmAddStartupObject(mainScene, createBox(260, 230));
    scmAddStartupObject(mainScene, createBox(360, 230));
    scmAddStartupObject(mainScene, createBox(460, 230));

    scmAddStartupObject(mainScene, createBox(220, 430));
    scmAddStartupObject(mainScene, createBox(360, 430));
    scmAddStartupObject(mainScene, createBox(460, 430));
    scmAddStartupObject(mainScene, createBox(560, 430));

    scmPushScene(mainScene);
}