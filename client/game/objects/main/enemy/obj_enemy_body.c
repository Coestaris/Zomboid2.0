//
// Created by maxim on 5/16/19.
//

#include "obj_enemy_body.h"

void body_update(gameObject_t* this, void* data)
{
    bodyData_t* bd = this->data;
    this->angle = twoPointsAngle(this->pos, bd->pd->pos);

    this->pos.x += cos(this->angle) * bd->speed;
    this->pos.y += sin(this->angle) * bd->speed;
}

void body_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, body_update);
}

int enemy_body_harm(double damage, gameObject_t* this)
{
    bodyData_t* bd = this->data;
    bd->hp -= damage;

    if(bd->hp <= 0) {
        spawnSpotBlood(20, 30, this->pos);
        scmDestroyObject(this, true);
        return 1;
    }

    return 0;
}


gameObject_t* createBody(playerData_t* player, vec_t pos)
{
    gameObject_t* this = object();
    this->drawable = 1;
    this->texID = TEXID_ENEMY_BODY;
    this->onInit = body_init;
    this->pos = pos;
    this->ID = OBJECT_BODY;

    allocData(bodyData_t, this, data);
    data->pd = player;
    data->speed = randRange(BODY_SPEED_MIN, BODY_SPEED_MAX);
    data->hp = BODY_HP;

    return this;
}