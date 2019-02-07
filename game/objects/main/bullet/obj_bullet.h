//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_OBJ_BULLET_H
#define ZOMBOID2_OBJ_BULLET_H

#define BULLET_SPEED 25
#define BULLET_LIGHT_ALPHA .02
#define BULLET_LIGHT_SIZE 1.3

#include "../../../objectInclude.h"
#include "../light/obj_light.h"

typedef struct _bulletData {

    gameObject* light;
    double xOffset;
    double yOffset;

} bulletData;

void bullet_event_update(gameObject *object, void *data);
void bullet_init(gameObject* object);
gameObject* createBullet(vec_t a, vec_t dir);

#endif //ZOMBOID2_OBJ_BULLET_H
