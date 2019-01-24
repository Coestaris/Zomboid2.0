//
// Created by maxim on 1/23/19.
//

#include "gameobject.h"

gameObject* object(void)
{
    gameObject* obj = malloc(sizeof(gameObject));
    obj->size = 0;
    obj->cachedTex = NULL;
    obj->init = NULL;
    obj->x = 0;
    obj->y = 0;
    obj->texID = -1;
    obj->data = NULL;
    obj->drawable = 0;
    obj->depth = 0;
    obj->frame = 0;
    obj->animationSpeed = 0;
    obj->animationCounter = 0;
    return obj;
}

void freeObject(gameObject *object)
{
    if(object->data) free(object->data);
    free(object);
}
