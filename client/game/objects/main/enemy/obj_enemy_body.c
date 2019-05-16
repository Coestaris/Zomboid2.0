//
// Created by maxim on 5/16/19.
//

#include "obj_enemy_body.h"

void body_update(gameObject_t* this, void* data)
{

}

void body_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, body_update);
}

gameObject_t* createBody(playerData_t* player, vec_t pos)
{
    gameObject_t* this = object();
    this->drawable = 1;
    this->texID = TEXID_ENEMY_BODY;

    allocData(bodyData_t, this, data);

    return this;
}