//
// Created by maxim on 1/24/19.
//

#ifndef ZOMBOID2_OBJ_BULLET_H
#define ZOMBOID2_OBJ_BULLET_H

#define BULLET_SPEED 15


#include "../../../objectInclude.h"

#include "../../bloodSpawner.h"
#include "../../score.h"
#include "../../enemy.h"

#include "../enemy/obj_enemy_tic.h"
#include "../enemy/obj_enemy_body.h"
#include "../enemy/obj_enemy_zombie.h"
#include "../enemy/obj_enemy_slug.h"
#include "../enemy/obj_enemy_ghost.h"
#include "../enemy/obj_enemy_slicer.h"

#include "../light/obj_light.h"
#include "obj_explosion.h"

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
