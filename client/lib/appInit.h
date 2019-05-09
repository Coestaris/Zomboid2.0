//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_APPINIT_H
#define ZOMBOID2_APPINIT_H

#include "GL/freeglut.h"
#include "GL/gl.h"

#include "resources/font.h"
#include "shaders/shaderManager.h"
#include "gameLogic/eventFuncs.h"
#include "gameLogic/gameScene.h"
#include "rlist/rlist.h"
#include "helpers.h"

#define OVERRIDE_GL_VERSION

#ifdef OVERRIDE_GL_VERSION
#define MAJOR_GL_VERSION 3
#define MINOR_GL_VERSION 0
#endif

void initGraphics(int argc, char** argv, int w, int h, const char* title, int isFixedSize, char* mainResFile);
void registerEvents();
void runApp(int sceneID);

#endif //ZOMBOID2_APPINIT_H
