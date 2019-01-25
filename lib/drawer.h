//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_DRAWER_H
#define ZOMBOID2_DRAWER_H

#include <math.h>

#include <GL/freeglut.h>
#include <GL/gl.h>

#include "tex.h"

void createPoint(double* x, double* y, double inx, double iny, double vcos, double vsin,
                 double hw, double hh, double cx, double cy, int s1, int s2);

void drawBackground(tex2d* tex, int frame, int windowW, int windowH);
void drawTexture(tex2d* tex, int frame, double x, double y, double angle, double scaleFactor);

void beginDraw(void);
void endDraw(void);

#endif //ZOMBOID2_DRAWER_H
