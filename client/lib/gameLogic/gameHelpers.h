//
// Created by maxim on 1/31/19.
//

#ifndef ZOMBOID2_GAMEHELPERS_H
#define ZOMBOID2_GAMEHELPERS_H

#include <stdio.h>
#include <math.h>

#include "gameobject.h"
#include "../graphics/drawer.h"
#include "../resources/tex.h"
#include "../resources/texManager.h"
#include "eventfuncs.h"

#include "../helpers.h"

void loadTexture(char* fn, int id, int scope, vec_t center, int mode);
void loadAnimation(int framesCount, int id, int scope, vec_t center, int mode, ...);
vec_t relativeCoordinates(gameObject_t* obj);
int isInWindowRect(gameObject_t* obj);
int isInWindowExtendedRect(gameObject_t* obj, int exW, int exH);
int isInObjectRect(gameObject_t* obj, vec_t point);

#endif //ZOMBOID2_GAMEHELPERS_H
