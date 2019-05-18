//
// Created by maxim on 5/16/19.
//

#include "obj_enemy_ghost.h"

void ghost_update(gameObject_t* this, void* data)
{
    ghostData_t* gd = this->data;
    this->angle = twoPointsAngle(this->pos, gd->pd->pos);

    this->pos.x += cos(this->angle) * gd->speed;
    this->pos.y += sin(this->angle) * gd->speed;
}

void ghost_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, ghost_update);
}

gameObject_t* createGhost(playerData_t* player, vec_t pos)
{
    gameObject_t* this = object();
    this->drawable = 1;
    this->texID = TEXID_ENEMY_GHOST;
    this->onInit = ghost_init;
    this->pos = pos;
    this->ID = OBJECT_GHOST;
    this->animationSpeed = GHOST_ANSPEED;

    allocData(ghostData_t, this, data);
    data->speed = randRange(GHOST_SPEED_MIN, GHOST_SPEED_MAX);
    data->hp = GHOST_HP;
    data->pd = player;

    return this;
}