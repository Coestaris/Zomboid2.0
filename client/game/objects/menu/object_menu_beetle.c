//
// Created by maxim on 5/4/19.
//

#include "object_menu_beetle.h"

void mbeetle_init(gameObject_t *this)
{
    evqSubscribeEvent(this, EVT_Update, mbeetle_event_update);
}

void mbeetle_event_update(gameObject_t *this, void* data)
{
    this->angle += randRange(-0.1, 0.1);

    this->pos.x += cos(this->angle) * 0.2;
    this->pos.y += sin(this->angle) * 0.2;
    //this->pos.y += ((mbeetleData_t*)this->data)->yOffset;

    if(isInWindowExtendedRect(this, MBEETLE_ROOM_OFFSET, MBEETLE_ROOM_OFFSET)) scmDestroyObject(this, true);
    if(getMouseState(MB_LEFT) == MS_PRESSED)
    {
        if(isInObjectRect(this, getMousePos()))
        {
            spawnSpotBlood(MBEETLE_BLOOD_COUNT, MBEETLE_BLOOD_RANGE, this->pos);
            scmDestroyObject(this, true);
        }
    }
}

gameObject_t* createMenuBeetle(vec_t pos, double angle, double speed)
{
    gameObject_t* this = object();
    this->drawable = 1;
    this->texID = TEXID_ENEMY_BEETLE;
    this->angle = angle;
    this->pos = pos;
    this->depth = 0;

    this->data = malloc(sizeof(mbeetleData_t));
    ((mbeetleData_t*)this->data)->xOffset = cos(angle) * speed;
    ((mbeetleData_t*)this->data)->yOffset = sin(angle) * speed;

    this->onInit = mbeetle_init;

    return this;
}
