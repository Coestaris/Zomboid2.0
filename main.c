#include <stdio.h>

#include "lib/graphics.h"

int main(int argc, char** argv) {

    initGraphics(argc, argv, 600, 600, "asd");
    registerEvents();

    glutMainLoop();
    //while(1);

    return 0;
}