//#include "game/game.h"

#include "lib/rlist/rlist.h"

int main(int argc, char** argv)
{
    rlist_init();

    const char* s = "../resources/defines.rlist";

    if(!fileExists(s)) {
        puts("File not exists");
        return 1;
    }

    rlist_load(s, true);

    /*
     * initGame(argc, argv);
     *  runGame();
     *
     *  */
    return 0;
}