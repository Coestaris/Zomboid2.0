//
// Created by maxim on 5/16/19.
//

#include "obj_enemy_slicer.h"

void slicer_update(gameObject_t* this, void* data)
{
    slicerData_t* sd = this->data;
    this->angle = twoPointsAngle(this->pos, sd->pd->pos);

    this->pos.x += cos(this->angle) * sd->speed;
    this->pos.y += sin(this->angle) * sd->speed;
}

void slicer_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, slicer_update);
}


int enemy_slicer_harm(double damage, gameObject_t* this)
{
    slicerData_t* sd = this->data;
    sd->hp -= damage;

    if(sd->hp <= 0) {
        spawnSpotBlood(20, 30, this->pos);
        scmDestroyObject(this, true);
        return 1;
    }

    return 0;
}

gameObject_t* createSlicer(playerData_t* player, vec_t pos)
{
    gameObject_t* this = object();
    this->drawable = 1;
    this->texID = TEXID_ENEMY_SLICER;
    this->onInit = slicer_init;
    this->pos = pos;
    this->ID = OBJECT_SLICER;

    allocData(slicerData_t, this, data);
    data->speed = randRange(SLICER_SPEED_MIN, SLICER_SPEED_MAX);
    data->hp = SLICER_HP;
    data->pd = player;

    return this;
}