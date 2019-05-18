//
// Created by maxim on 5/16/19.
//

#ifndef ZOMBOID2_OBJ_ENEMY_BODY_H
#define ZOMBOID2_OBJ_ENEMY_BODY_H

#include "../../../objectInclude.h"
#include "../../bloodSpawner.h"
#include "../../playerData.h"
#include "../../enemy.h"

typedef struct _bodyData {
    playerData_t* pd;
    double hp;
    double speed;

} bodyData_t;

int enemy_body_harm(double damage, gameObject_t* this);
gameObject_t* createBody(playerData_t* player, vec_t pos);

#endif //ZOMBOID2_OBJ_ENEMY_BODY_H
