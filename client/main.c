#include "game/game.h"

//#include "lib/graphics/shader.h"

int main(int argc, char** argv)
{
    initGame(argc, argv);
/*

    shader* sh = createShader("../resources/shaders/test/shader.fsh",
                              "../resources/shaders/test/shader.vsh");

    if(!loadShader(sh)) {
        exit(0);
    }*/

    runGame();

    return 0;
}