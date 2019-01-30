//
// Created by maxim on 1/29/19.
//

#ifndef ZOMBOID2_OBJ_ENEMY_H
#define ZOMBOID2_OBJ_ENEMY_H

#include "../../../objectInclude.h"

#define ENEMY_SPEED_MAX 0.5
#define ENEMY_SPEED_MIN 0.1

typedef struct enemyData {
    gameObject* player;

    tex2d* larm_tex;
    tex2d* rarm_tex;

    int larm;
    int rarm;

    double speed;

} enemyData;

void enemy_init(gameObject* this);
void enemy_event_update(gameObject* this, void* data);
gameObject* createEnemy(gameObject* player, double x, double y);

#endif //ZOMBOID2_OBJ_ENEMY_H
