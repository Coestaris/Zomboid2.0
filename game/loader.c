//
// Created by maxim on 1/24/19.
//

#include "loader.h"
#include "objects/main/light/obj_rotatable_light.h"

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

    scmAddStartupObject(mainScene, createBox(250, 150));
    scmAddStartupObject(mainScene, createBox(350, 150));
    scmAddStartupObject(mainScene, createBox(450, 150));
    scmAddStartupObject(mainScene, createBox(550, 150));

    scmAddStartupObject(mainScene, createBox(250, 210));
    scmAddStartupObject(mainScene, createBox(250, 390));

    scmAddStartupObject(mainScene, createBox(550, 210));
    scmAddStartupObject(mainScene, createBox(550, 390));

    scmAddStartupObject(mainScene, createBox(250, 450));
    scmAddStartupObject(mainScene, createBox(350, 450));
    scmAddStartupObject(mainScene, createBox(450, 450));
    scmAddStartupObject(mainScene, createBox(550, 450));

    //scmAddStartupObject(mainScene, createBox(550, 210));
    //scmAddStartupObject(mainScene, createBox(550, 270));
    //scmAddStartupObject(mainScene, createBox(550, 330));
    //scmAddStartupObject(mainScene, createBox(550, 390));


    scmAddStartupObject(mainScene, create_rotatableLight(vec(150, 150), 0.01,
            createTexturedDirectLT(vec(0, 0), 800, 0, 400, 600, color(1, 0, 1, 0.5), texmGetID(TEXID_LIGHT_DUO), 0, vec(1, 1))));

    scmAddStartupObject(mainScene, create_rotatableLight(vec(650, 450), 0.012,
            createTexturedDirectLT(vec(0, 0), 800, 0, 400, 600, color(0, 1, 1, 0.5), texmGetID(TEXID_LIGHT_DUO), 0, vec(1, 1))));

    scmAddStartupObject(mainScene, create_rotatableLight(vec(150, 450), 0.013,
            createTexturedDirectLT(vec(0, 0), 800, 0, 400, 600, color(1, 1, 0, 0.5), texmGetID(TEXID_LIGHT_DUO), 0, vec(1, 1))));

    scmAddStartupObject(mainScene, create_rotatableLight(vec(650, 150), 0.015,
            createTexturedDirectLT(vec(0, 0), 800, 0, 400, 600, color(0, 1, 0, 0.6), texmGetID(TEXID_LIGHT_DUO), 0, vec(1, 1))));

    scmAddStartupObject(mainScene, create_rotatableLight(vec(400, 300), 0.005,
            createTexturedDirectLT(vec(0, 0), 1200, 0, 400, 600, color(0, 0, 1, 0.6), texmGetID(TEXID_LIGHT_DUO), 0, vec(1, 1))));


    scmAddStartupObject(mainScene, createTexturedAreaLT(vec(150, 150), 600, color(1, 0, 0, 0.2), texmGetID(TEXID_LIGHT), 0));
    scmAddStartupObject(mainScene, createTexturedAreaLT(vec(650, 450), 600, color(0, 1, 1, 0.3), texmGetID(TEXID_LIGHT), 0));
    scmAddStartupObject(mainScene, createTexturedAreaLT(vec(150, 450), 600, color(1, 1, 0, 0.4), texmGetID(TEXID_LIGHT), 0));
    scmAddStartupObject(mainScene, createTexturedAreaLT(vec(650, 150), 600, color(0, 1, 0, 0.5), texmGetID(TEXID_LIGHT), 0));

    scmAddStartupObject(mainScene, createTexturedAreaLT(vec(400, 300), 800, color(0, 0, 1, 0.4), texmGetID(TEXID_LIGHT), 0));



    scmPushScene(mainScene);
}