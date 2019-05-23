//
// Created by maxim on 1/24/19.
//

#include "game.h"

void initGame(int argc, char** argv)
{
    initPublicObjects();
    initGraphics(argc, argv, 1000, 800, "GAME", false, "../resources/resources.rlist");
    loadResources();

    bloodSpawnerInit();
}

void runGame(void)
{
    runApp(0);
}