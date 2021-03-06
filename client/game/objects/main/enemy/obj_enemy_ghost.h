//
// Created by maxim on 5/16/19.
//

#ifndef ZOMBOID2_OBJ_ENEMY_GHOST_H
#define ZOMBOID2_OBJ_ENEMY_GHOST_H

#include "../../../objectInclude.h"
#include "../../playerData.h"
#include "../../enemy.h"
#include "../../bloodSpawner.h"

typedef struct _ghostData {
    playerData_t* pd;
    double speed;
    double hp;

} ghostData_t;

int enemy_ghost_harm(double damage, gameObject_t* this);
gameObject_t* createGhost(playerData_t* player, vec_t pos);

#endif //ZOMBOID2_OBJ_ENEMY_GHOST_H
