//
// Created by maxim on 1/26/19.
//

#ifndef ZOMBOID2_SURFACE_H
#define ZOMBOID2_SURFACE_H

#include <GL/freeglut.h>
#include <GL/gl.h>

#include "../resources/tex.h"

void srfInit(int wW, int wH);
void srfClear();
void srfBind();
void srfFree();
void srfDrawTexture(tex_t* tex, int frame, double alpha, vec_t pos, int flipX, int flipY);

#endif //ZOMBOID2_SURFACE_H
