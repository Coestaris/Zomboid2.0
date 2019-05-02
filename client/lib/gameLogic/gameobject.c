//
// Created by maxim on 1/23/19.
//

#include "gameobject.h"

gameObject_t* object(void)
{
    gameObject_t* obj = malloc(sizeof(gameObject_t));
    obj->size = 1;
    obj->cachedTex = NULL;
    obj->onInit = NULL;
    obj->onDestroy = NULL;
    obj->pos = vec(0, 0);
    obj->texID = -1;
    obj->data = NULL;
    obj->drawable = 0;
    obj->depth = 0;
    obj->frame = 0;
    obj->angle = 0;
    obj->alpha = 1;
    obj->animationSpeed = 0;
    obj->animationCounter = 0;
    return obj;
}

void freeObject(gameObject_t *object)
{
    if(object->onDestroy) object->onDestroy(object);
    if(object->data) free(object->data);
    free(object);
}
