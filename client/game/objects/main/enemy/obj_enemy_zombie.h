//
// Created by maxim on 1/29/19.
//

#ifndef ZOMBOID2_OBJ_ENEMY_H
#define ZOMBOID2_OBJ_ENEMY_H

#include "../../../objectInclude.h"

#include "../../bloodSpawner.h"
#include "../../playerData.h"

#define ENEMY_SPEED_MAX 0.5
#define ENEMY_SPEED_MIN 0.1

#define ENEMY_HP 100.0

typedef struct _zombieData
{
    double hp;
    playerData_t* player;

    int larm;
    double speed;

} zombieData_t;

void enemy_zombie_harm(double damage, gameObject_t* this);
gameObject_t* createEnemy(playerData_t* player, vec_t pos);

#endif //ZOMBOID2_OBJ_ENEMY_H
