//
// Created by maxim on 5/16/19.
//

#include "obj_enemy_tic.h"

void tic_update(gameObject_t* this, void* data)
{
    ticData_t* td = this->data;
    this->pos.x += td->xOffset;
    this->pos.y += td->yOffset;

    if (isInWindowExtendedRect(this, MBEETLE_ROOM_OFFSET, MBEETLE_ROOM_OFFSET))
        scmDestroyObject(this, true);
}

void tic_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, tic_update);
}


int enemy_tic_harm(double damage, gameObject_t* this)
{
    ticData_t* td = this->data;
    td->hp -= damage;

    if(td->hp <= 0) {
        spawnSpotBlood(20, 30, this->pos);
        srfDrawTexture(texmGetID(TEXID_BEETLE_DEAD), 0, color(1, 1, 1, 1), this->pos, randAngle(), randRange(0.9, 1.1));
        scmDestroyObject(this, true);
        return 1;
    }

    return 0;
}


gameObject_t* createTic(playerData_t* player, vec_t pos, double angle)
{
    gameObject_t* this = object();
    this->drawable = 1;
    this->texID = TEXID_ENEMY_BEETLE;
    this->onInit = tic_init;
    this->angle = angle;
    this->pos = pos;
    this->ID = OBJECT_TIC;

    this->collisionXExt = 5;
    this->collisionYExt = 5;

    allocData(ticData_t, this, data);
    data->xOffset = cos(angle) * TIC_SPEED;
    data->yOffset = sin(angle) * TIC_SPEED;
    data->hp = TIC_HP;

    return this;
}