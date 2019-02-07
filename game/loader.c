//
// Created by maxim on 1/24/19.
//

#include "loader.h"

void mainScene_onLoad(gameScene* scene) {
    updateEdges(TEXID_BOX);
}

void initScenes(void)
{
    gameScene* mainScene = createScene(SCENEID_MAIN, 0);
    mainScene->backgroundTexId = TEXID_BACK_CONCRETE;
    mainScene->onLoad = mainScene_onLoad;

    gameObject* player = createPlayer();
    scmAddStartupObject(mainScene, player);

    scmAddStartupObject(mainScene, createBox(400, 300));
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
/*
    scmAddStartupObject(mainScene, createTexturedAreaLT(vec(200, 200), 600, color(1, 0, 0, 0.3), texmGetID(TEXID_LIGHT), 0));
    scmAddStartupObject(mainScene, createTexturedAreaLT(vec(605, 510), 600, color(0, 1, 1, 0.3), texmGetID(TEXID_LIGHT), 0));
    scmAddStartupObject(mainScene, createTexturedAreaLT(vec(205, 515), 600, color(1, 1, 0, 0.3), texmGetID(TEXID_LIGHT), 0));
    scmAddStartupObject(mainScene, createTexturedAreaLT(vec(605, 215), 600, color(0, 1, 0, 0.3), texmGetID(TEXID_LIGHT), 0));
*/

    scmPushScene(mainScene);
}