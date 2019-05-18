//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_OBJ_BULLET_H
#define ZOMBOID2_OBJ_BULLET_H

#define BULLET_SPEED 15
#define BULLET_LIGHT_ALPHA .15
#define BULLET_LIGHT_SIZE 400

#include "../../enemy.h"

#include "../../../objectInclude.h"

#include "../../bloodSpawner.h"
#include "../../score.h"

#include "../enemy/obj_enemy_zombie.h"
#include "../enemy/obj_enemy_tic.h"

#include "../light/obj_light.h"

typedef struct _bulletData
{
    gameObject_t* light;
    gameMobData_t* md;
    double xOffset;
    double yOffset;
    double damage;

} bulletData_t;

gameObject_t* createBullet(gameMobData_t* md, vec_t p, double angle, int texID, double damage);

#endif //ZOMBOID2_OBJ_BULLET_H
