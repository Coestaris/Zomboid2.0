//
// Created by maxim on 1/22/19.
//

#ifndef ZOMBOID2_DRAWER_H
#define ZOMBOID2_DRAWER_H

#include <math.h>

#include <GL/freeglut.h>
#include <GL/gl.h>

#include "tex.h"

void createPoint(double* x, double* y, double inx, double iny, double vcos, double vsin, double hw, double hh, int s1, int s2);

void drawTexture(tex2d* tex, double x, double y, double angle, double scaleFactor);

#endif //ZOMBOID2_DRAWER_H
