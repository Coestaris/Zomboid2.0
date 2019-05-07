//
// Created by maxim on 1/24/19.
//

#include "game.h"

void initGame(int argc, char** argv)
{
    initPublicObjects();
    initGraphics(argc, argv, 800, 600, "GAME", true, "../resources/resources.rlist");
    loadResources();
    bloodSpawnerInit();
}

void runGame(void)
{
    runApp(0);
}