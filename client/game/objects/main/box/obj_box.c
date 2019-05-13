//
// Created by maxim on 1/25/19.
//

#include "obj_box.h"


void box_init(gameObject_t* this)
{
    const double w = 32;
    const double h = 32;

    ltracerPushEdge(
            vec(this->pos.x + w * cos(this->angle + 1 * M_PI_4), this->pos.y + h * sin(this->angle + 1 * M_PI_4)),
            vec(this->pos.x + w * cos(this->angle + 3 * M_PI_4), this->pos.y + h * sin(this->angle + 3 * M_PI_4)),
            vec(this->pos.x + w * cos(this->angle + 5 * M_PI_4), this->pos.y + h * sin(this->angle + 5 * M_PI_4)),
            vec(this->pos.x + w * cos(this->angle + 7 * M_PI_4), this->pos.y + h * sin(this->angle + 7 * M_PI_4)));
}

gameObject_t* createBox()
{
    gameObject_t* go = object();
    go->drawable = true;
    go->size = 1.5;
    go->texID = TEXID_BOX;
    go->ID = OBJECT_BOX;
    go->onInit = box_init;
    go->depth = 2;

    return go;
}