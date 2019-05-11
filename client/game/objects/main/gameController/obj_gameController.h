//
// Created by maxim on 5/11/19.
//

#ifndef ZOMBOID2_GAMECONTROLLER_H
#define ZOMBOID2_GAMECONTROLLER_H

#include "../../../objectInclude.h"

#include "../../weapon.h"
#include "../enemy/obj_enemy_zombie.h"
#include "../../playerData.h"

//todo: Replace by real define!!!!!!
#define ASD 10

typedef struct _gameController_data {

    int wave;
    double completed;

    //todo: Insert zsize_t type here
    int playerCount;

    playerData_t* players[ASD];

} gameControllerData_t ;

gameObject_t* createGameController();

#endif //ZOMBOID2_GAMECONTROLLER_H
