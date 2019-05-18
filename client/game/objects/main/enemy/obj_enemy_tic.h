//
// Created by maxim on 5/16/19.
//

#ifndef ZOMBOID2_OBJ_ENEMY_TIC_H
#define ZOMBOID2_OBJ_ENEMY_TIC_H

#include "../../menu/object_menu_beetle.h"
#include "../../../objectInclude.h"
#include "../../playerData.h"
#include "../../enemy.h"

typedef struct _ticData {
    double xOffset;
    double yOffset;
    double hp;

} ticData_t;

int enemy_tic_harm(double damage, gameObject_t* this);
gameObject_t* createTic(playerData_t* player, vec_t pos, double angle);

#endif //ZOMBOID2_OBJ_ENEMY_TIC_H
