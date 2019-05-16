//
// Created by maxim on 5/16/19.
//

#include "obj_enemy_slicer.h"

void slicer_update(gameObject_t* this, void* data)
{

}

void slicer_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, slicer_update);
}

gameObject_t* createSlicer(playerData_t* player, vec_t pos)
{
    gameObject_t* this = object();
    this->drawable = 1;
    this->texID = TEXID_ENEMY_SLICER;

    allocData(slicerData_t, this, data);

    return this;
}