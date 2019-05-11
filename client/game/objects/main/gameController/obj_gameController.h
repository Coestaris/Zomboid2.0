//
// Created by maxim on 5/11/19.
//

#ifndef ZOMBOID2_GAMECONTROLLER_H
#define ZOMBOID2_GAMECONTROLLER_H

#include "../../../objectInclude.h"

typedef struct _gameController_data {
    int wave;
    double completed;

} gameControllerData_t ;

gameObject_t* createGameController();

#endif //ZOMBOID2_GAMECONTROLLER_H
