//
// Created by maxim on 1/29/19.
//

#ifndef ZOMBOID2_OBJ_ENEMY_H
#define ZOMBOID2_OBJ_ENEMY_H

#include "../../../objectInclude.h"

#include "../../bloodSpawner.h"

#define ENEMY_SPEED_MAX 0.5
#define ENEMY_SPEED_MIN 0.1

#define ENEMY_HP 100.0

typedef struct enemyData
{
    double hp;

    gameObject_t* player;

    tex_t* larm_tex;
    tex_t* rarm_tex;

    int larm;


    double speed;

} enemyData_t;

void enemy_zombie_harm(gameObject_t* this);
void enemy_init(gameObject_t* this);
void enemy_event_update(gameObject_t* this, void* data);
gameObject_t* createEnemy(gameObject_t* player, vec_t pos);

#endif //ZOMBOID2_OBJ_ENEMY_H
