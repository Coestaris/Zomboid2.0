//
// Created by maxim on 1/25/19.
//

#include "obj_box.h"

void box_init(gameObject* object)
{

}

void box_event_update(gameObject *object, void *data)
{

}

gameObject* createBox(int x, int y)
{
    gameObject* go = object();
    go->drawable = true;
    go->size = 1.5;
    go->x =x;
    go->y = y;
    go->texID = TEXID_BOX;
    return go;
}