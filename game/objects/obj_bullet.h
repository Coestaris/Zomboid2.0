//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_OBJ_BULLET_H
#define ZOMBOID2_OBJ_BULLET_H

#include "../objectInclude.h"

#define BULLET_SPEED 15

void bullet_event_update(gameObject *object, void *data);
void bullet_init(gameObject* object);
gameObject* createBullet(double x, double y, double dirx, double diry);

#endif //ZOMBOID2_OBJ_BULLET_H
