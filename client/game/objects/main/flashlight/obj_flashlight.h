//
// Created by maxim on 1/26/19.
//

#ifndef ZOMBOID2_OBJ_FLASHLIGHT_H
#define ZOMBOID2_OBJ_FLASHLIGHT_H

#include "../../../objectInclude.h"

typedef struct _flashlightData{

    gameObject* player;
    double minSize;

} flashlightData;

gameObject* createFlashlight(gameObject* player, double minSize, double alpha);

#endif //ZOMBOID2_OBJ_FLASHLIGHT_H
