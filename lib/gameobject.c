//
// Created by maxim on 1/23/19.
//

#include "gameobject.h"

void freeObject(gameObject *object)
{
    if(object->data) free(object->data);
    free(object);
}
