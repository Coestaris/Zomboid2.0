//
// Created by maxim on 5/10/19.
//

#ifndef ZOMBOID2_OBJ_HUD_H
#define ZOMBOID2_OBJ_HUD_H

#include "../../../objectInclude.h"

#include "../gameController/obj_gameController.h"

typedef struct _hudData {
    playerData_t* playerData;
    gameMobData_t* md;
    gameControllerData_t* gcData;

} hudData_t;

gameObject_t* createHud(void);

#endif //ZOMBOID2_OBJ_HUD_H
