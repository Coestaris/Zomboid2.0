//
// Created by maxim on 5/16/19.
//

#ifndef ZOMBOID2_OBJ_ENEMY_SLUG_H
#define ZOMBOID2_OBJ_ENEMY_SLUG_H

#include "../../../objectInclude.h"
#include "../../playerData.h"
#include "../../enemy.h"
#include "../../bloodSpawner.h"

typedef struct _slugData {
    playerData_t* pd;
    double speed;
    double hp;
    double frame;

} slugData_t;

int enemy_slug_harm(double damage, gameObject_t* this);
gameObject_t* createSlug(playerData_t* player, vec_t pos);

#endif //ZOMBOID2_OBJ_ENEMY_SLUG_H
