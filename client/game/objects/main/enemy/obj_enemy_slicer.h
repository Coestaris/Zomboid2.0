//
// Created by maxim on 5/16/19.
//

#ifndef ZOMBOID2_OBJ_ENEMY_SLICER_H
#define ZOMBOID2_OBJ_ENEMY_SLICER_H

#include "../../../objectInclude.h"
#include "../../playerData.h"
#include "../../enemy.h"
#include "../../bloodSpawner.h"

typedef struct _slicerData {
    playerData_t* pd;
    double speed;
    double frame;
    double hp;

} slicerData_t;

int enemy_slicer_harm(double damage, gameObject_t* this);
gameObject_t* createSlicer(playerData_t* player, vec_t pos);

#endif //ZOMBOID2_OBJ_ENEMY_SLICER_H
