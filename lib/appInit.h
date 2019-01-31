//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_APPINIT_H
#define ZOMBOID2_APPINIT_H

#include "GL/freeglut.h"
#include "GL/gl.h"

#include "eventfuncs.h"
#include "gameScene.h"
#include "helpers.h"
#include "rlist/rlist.h"

void initGraphics(int argc, char **argv, int w, int h, const char *title, int isFixedSize, char* mainResFile);
void registerEvents();
void runApp(int sceneID);

#endif //ZOMBOID2_APPINIT_H
