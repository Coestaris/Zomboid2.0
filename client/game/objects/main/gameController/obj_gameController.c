//
// Created by maxim on 5/11/19.
//

#include "obj_gameController.h"

void gc_update(gameObject_t* this, void* data)
{
    gameControllerData_t* gd = this->data;
    gd->completed += 0.6;
    if(gd->completed > 100)
    {
        gd->completed = 0;
        gd->wave++;
    }

}

void gc_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, gc_update);
}

gameObject_t* createGameController()
{
    gameObject_t* obj = object();
    obj->onInit = gc_init;
    obj->ID = OBJECT_GAME_CONTROLLER;

    allocData(gameControllerData_t, obj, data);
    data->wave = 4;
    data->completed = 0;

    return obj;
}