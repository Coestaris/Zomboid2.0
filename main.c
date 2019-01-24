#include <stdio.h>

#include "lib/graphics.h"

#include "lib/tex.h"
#include "lib/texManager.h"
#include "lib/gameScene.h"

#include "game/objects/obj_player.h"

void loadTexture(const char* fn, int id, int scope)
{
    if(fileExists(fn))
    {
        texmPush(createTex(fn, id, scope));
    }
    else
    {
        printf("Unable to reach file \"%s\"", fn);
        exit(1);
    }
}

#define SCENEID_MAIN 0

int main(int argc, char** argv) {

    initGraphics(argc, argv, 600, 600, "asd");
    registerEvents();
    texmInit();

    loadTexture("in.png",  1, 0);
    loadTexture("in1.png", 2, 0);
    loadTexture("in2.png", 3, 0);

    gameScene* mainScene = createScene(SCENEID_MAIN, 0);
    addStarupObject(mainScene, createPlayer());

    pushScene(mainScene);

    run(SCENEID_MAIN);

    texmFreeScope(0);
    return 0;
}