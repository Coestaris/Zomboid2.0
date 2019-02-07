//
// Created by maxim on 1/26/19.
//

#include "obj_light.h"

gameObject* createLight(vec_t p, double size, double alpha)
{
    gameObject* go = object();
    go->drawable = true;

    go->depth = 0;
    go->pos = p;

    go->texID = TEXID_LIGHT;
    go->size = size;
    go->alpha = alpha;
    return go;
}
