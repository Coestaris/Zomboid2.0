//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_APPINIT_H
#define ZOMBOID2_APPINIT_H

#include "GL/freeglut.h"
#include "GL/gl.h"

#include "gameLogic/eventfuncs.h"
#include "gameLogic/gameScene.h"
#include "helpers.h"
#include "rlist/rlist.h"

#define OVERRIDE_GL_VERSION

#ifdef OVERRIDE_GL_VERSION
    #define MAJOR_GL_VERSION 4
    #define MINOR_GL_VERSION 2
#endif

void initGraphics(int argc, char **argv, int w, int h, const char *title, int isFixedSize, char* mainResFile);
void registerEvents();
void runApp(int sceneID);

#endif //ZOMBOID2_APPINIT_H
