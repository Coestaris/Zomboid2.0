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

void loadTexture(char* fn, int id, int scope, vec_t center, int mode);
void loadAnimation(int framesCount, int id, int scope, vec_t center, int mode, ...);
vec_t relativeCoordinates(gameObject* obj);
int isInWindowRect(gameObject* obj);
int isInWindowExtendedRect(gameObject* obj, int exW, int exH);
int isInObjectRect(gameObject* obj, vec_t point);

#endif //ZOMBOID2_GAMEHELPERS_H
