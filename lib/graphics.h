//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_GRAPHICS_H
#define ZOMBOID2_GRAPHICS_H

#include "GL/freeglut.h"
#include "GL/gl.h"

#include "eventfuncs.h"

void initGraphics(int argc, char** argv, int w, int h, const char* title);
void registerEvents();

#endif //ZOMBOID2_GRAPHICS_H
