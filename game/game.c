//
// Created by maxim on 1/24/19.
//

#include "game.h"

void initGame(int argc, char** argv)
{
    initGraphics(argc, argv, 600, 600, "asd", true);
    registerEvents();
    texmInit();

    loadTextures();
    initScenes();
}

void runGame(void)
{
    run(SCENEID_MAIN);
}