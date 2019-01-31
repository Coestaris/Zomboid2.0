//
// Created by maxim on 1/31/19.
//

#ifndef ZOMBOID2_GAMEHELPERS_H
#define ZOMBOID2_GAMEHELPERS_H

#include <stdio.h>
#include <math.h>

#include "gameobject.h"
#include "drawer.h"
#include "tex.h"
#include "texManager.h"
#include "eventfuncs.h"

#include "helpers.h"

void loadTexture(const char* fn, int id, int scope, double cX, double cY, int mode);
void loadAnimation(int framesCount, int id, int scope, double cX, double cY, int mode, ...);
void relativeCoordinates(double* x, double* y, gameObject* obj);
int isInWindowRect(gameObject* obj);

#endif //ZOMBOID2_GAMEHELPERS_H
