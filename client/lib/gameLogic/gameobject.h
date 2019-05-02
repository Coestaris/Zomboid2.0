//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_GAMEOBJECT_H
#define ZOMBOID2_GAMEOBJECT_H

#include <malloc.h>

#include "../resources/tex.h"

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

    tex_t* cachedTex;

    void* data;

    void (*onInit)(struct _GameObject* object);
    void (*onDestroy)(struct _GameObject* object);

} gameObject_t;

gameObject_t* object();
void freeObject(gameObject_t* object);

#endif //ZOMBOID2_GAMEOBJECT_H
