//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_GAMEOBJECT_H
#define ZOMBOID2_GAMEOBJECT_H

#include <malloc.h>

#include "tex.h"

typedef struct _GameObject
{
    int drawable;

    int texID;
    vec_t pos;

    double angle;
    double size;
    double alpha;

    int frame;
    int depth;

    int animationSpeed;
    int animationCounter;

    tex2d* cachedTex;

    void* data;

    void (*onInit)(struct _GameObject* object);
    void (*onDestroy)(struct _GameObject* object);

} gameObject;

gameObject* object();
void freeObject(gameObject* object);

#endif //ZOMBOID2_GAMEOBJECT_H
