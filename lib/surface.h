//
// Created by maxim on 1/26/19.
//

#ifndef ZOMBOID2_SURFACE_H
#define ZOMBOID2_SURFACE_H

#include <GL/freeglut.h>
#include <GL/gl.h>

#include "tex.h"

void srfInit(int winW, int winH);
void srfClear();
void srfDrawTexture(tex2d* tex, double x, double y);

#endif //ZOMBOID2_SURFACE_H
