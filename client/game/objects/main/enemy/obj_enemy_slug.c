//
// Created by maxim on 5/16/19.
//

#include "obj_enemy_slug.h"

void slug_update(gameObject_t* this, void* data)
{
    slugData_t* sd = this->data;
    this->angle = twoPointsAngle(this->pos, sd->pd->pos);

    this->pos.x += cos(this->angle) * sd->speed;
    this->pos.y += sin(this->angle) * sd->speed;
}

void slug_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, slug_update);
}

gameObject_t* createSlug(playerData_t* player, vec_t pos)
{
    gameObject_t* this = object();
    this->drawable = 1;
    this->texID = TEXID_ENEMY_SLUG;
    this->onInit = slug_init;
    this->pos = pos;
    this->ID = OBJECT_SLUG;
    this->animationSpeed = SLUG_ANSPEED;

    allocData(slugData_t, this, data);
    data->speed = randRange(SLUG_SPEED_MIN, SLUG_SPEED_MAX);
    data->hp = SLUG_HP;
    data->pd = player;

    return this;
}