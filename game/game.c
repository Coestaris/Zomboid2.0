//
// Created by maxim on 1/24/19.
//

#include "game.h"

void initGame(int argc, char** argv)
{
    initGraphics(argc, argv, 800, 600, "GAME", true);
    initEventFuncs();
    registerEvents();
    texmInit();

    loadTextures();
    initScenes();
}

void runGame(void)
{
    runApp(SCENEID_MAIN);
}