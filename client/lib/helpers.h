//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_HELPERS_H
#define ZOMBOID2_HELPERS_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include  "structs.h"

#define true 1
#define TRUE 1
#define false 0
#define FALSE 0
#define glCheck(file,s) if((glerror = glGetError()) != GL_NO_ERROR) { printf(file"[ERROR]: "s".Gl error: %i (%s)\n", glerror, gluErrorString(glerror)); return 0; }

int randBool();
double randAngle();
int randIntRange(int a, int b);
double randRange(double a, double b);
color_t randColor(double alpha);
vec_t randVector(double maxW, double maxH);
int fileExists(const char* filename);
double twoPointsAngle(vec_t p1, vec_t p2);
double distance(vec_t p1, vec_t p2);
double toRad(double angle);
double toDeg(double angle);
void createRotatedPoint(vec_t* p, vec_t inp, double vcos, double vsin, double hw, double hh, vec_t cp, int s1, int s2);

#endif //ZOMBOID2_HELPERS_H
