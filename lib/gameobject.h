//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_GAMEOBJECT_H
#define ZOMBOID2_GAMEOBJECT_H

#include <malloc.h>

#include "tex.h"
#include "helpers.h"

typedef struct _GameObject
{
    int drawable;

    int texID;
    double x;
    double y;
    double angle;
    double size;

    tex2d* cachedTex;

    void* data;
    void (*init)(struct _GameObject* object);

} gameObject;

gameObject* object();
void freeObject(gameObject* object);

#endif //ZOMBOID2_GAMEOBJECT_H
