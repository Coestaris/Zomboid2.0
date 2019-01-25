//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_HELPERS_H
#define ZOMBOID2_HELPERS_H

#include <stdio.h>
#include <math.h>

#include "gameobject.h"
#include "drawer.h"
#include "tex.h"
#include "texManager.h"

#define true 1
#define TRUE 1
#define false 0
#define FALSE 0

int fileExists(const char* filename);
double toPointsAngle(double x1, double y1, double x2, double y2);
double randRange(double a, double b);

void loadTexture(const char* fn, int id, int scope, int cX, int cY, int isBg);
void loadAnimation(int framesCount, int id, int scope, int cX, int cY, ...);

void relativeCoordinates(double* x, double* y, gameObject* obj);
int isInWindowRect(gameObject* obj);

double toRad(double angle);
double toDeg(double angle);

#endif //ZOMBOID2_HELPERS_H
