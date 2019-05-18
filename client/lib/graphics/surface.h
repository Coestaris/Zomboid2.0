//
// Created by maxim on 1/26/19.
//

#ifndef ZOMBOID2_SURFACE_H
#define ZOMBOID2_SURFACE_H

#include <GL/freeglut.h>
#include <GL/gl.h>

#include "../helpers.h"
#include "../resources/tex.h"

int srfInit();
int srfClear();
void srfBind();
int srfFree();
void srfRealloc();
void srfDrawTexture(tex_t* tex, int frame, color_t color, vec_t pos, double angle, double scaleFactor);

#endif //ZOMBOID2_SURFACE_H
