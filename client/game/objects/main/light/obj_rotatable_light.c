//
// Created by maxim on 2/8/19.
//

#include "obj_rotatable_light.h"

void rotatableLight_update(gameObject_t* this, void* data)
{
    rotatableLight_data_t* ld = (rotatableLight_data_t*) this->data;
    ld->obj->angle += ld->speed;
    ld->obj->pos = vec_add(this->pos, vec_mult(vec(
            cos(ld->obj->angle), sin(ld->obj->angle)), 40));
}

void rotatableLight_init(gameObject_t* this)
{
    rotatableLight_data_t* ld = (rotatableLight_data_t*) this->data;

    evqSubscribeEvent(this, EVT_Update, rotatableLight_update);
    scmPushObject(ld->obj);
}

gameObject_t* create_rotatableLight(vec_t pos, double speed, gameObject_t* light)
{
    gameObject_t* this = object();
    this->data = malloc(sizeof(rotatableLight_data_t));
    rotatableLight_data_t* ld = (rotatableLight_data_t*) this->data;

    ld->speed = speed;
    ld->obj = light;
    light->pos = pos;
    this->pos = pos;
    light->angle = randAngle();

    this->pos = pos;

    this->onInit = rotatableLight_init;

    return this;
}