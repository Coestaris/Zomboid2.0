//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_OBJ_BULLET_H
#define ZOMBOID2_OBJ_BULLET_H

#define BULLET_SPEED 15
#define BULLET_LIGHT_ALPHA .3
#define BULLET_LIGHT_SIZE 400

#include "../../../objectInclude.h"
#include "../light/obj_light.h"

typedef struct _bulletData
{

    gameObject_t* light;
    double xOffset;
    double yOffset;

} bulletData_t;

void bullet_event_update(gameObject_t* object, void* data);
void bullet_init(gameObject_t* object);
gameObject_t* createBullet(vec_t a, double angle);

#endif //ZOMBOID2_OBJ_BULLET_H
