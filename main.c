//#include "game/game.h"

#include "lib/rlist/rlist.h"

int main(int argc, char** argv)
{
    texmInit();
    rlist_init();

    const char* s = "../resources/images.rlist";

    if(!fileExists(s)) {
        puts("File not exists");
        return 1;
    }

    rlist_load((char*)s, true);

    /*
     * initGame(argc, argv);
     *  runGame();
     *
     *  */
    return 0;
}