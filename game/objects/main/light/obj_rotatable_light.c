//
// Created by maxim on 2/8/19.
//

#include "obj_rotatable_light.h"

void rotatableLight_update(gameObject* this, void* data)
{
    rotatableLight_data* ld = (rotatableLight_data*)this->data;
    ld->obj->angle += ld->speed;
    ld->obj->pos = vec_add(this->pos, vec_mult(vec(
            cos(ld->obj->angle), sin(ld->obj->angle)), 40));
}

void rotatableLight_init(gameObject* this)
{
    rotatableLight_data* ld = (rotatableLight_data*)this->data;

    evqSubscribeEvent(this, EVT_Update, rotatableLight_update);
    scmPushObject(ld->obj);
}

gameObject* create_rotatableLight(vec_t pos, double speed, gameObject* light)
{
    gameObject* this = object();
    this->data = malloc(sizeof(rotatableLight_data));
    rotatableLight_data* ld = (rotatableLight_data*)this->data;

    ld->speed = speed;
    ld->obj = light;
    light->pos = pos;
    this->pos = pos;
    light->angle = randRange(0, M_2_PI);

    this->pos = pos;

    this->onInit = rotatableLight_init;

    return this;
}