//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_GAMEOBJECT_H
#define ZOMBOID2_GAMEOBJECT_H

#include <malloc.h>

typedef struct _GameObject
{
    int texID;
    double x;
    double y;
    double angle;

    void* data;
    void (*init)(struct _GameObject* object);

} gameObject;

#endif //ZOMBOID2_GAMEOBJECT_H
