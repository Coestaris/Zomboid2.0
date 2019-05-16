//
// Created by maxim on 5/16/19.
//

#ifndef ZOMBOID2_OBJ_ENEMY_BODY_H
#define ZOMBOID2_OBJ_ENEMY_BODY_H

#include "../../../objectInclude.h"
#include "../../playerData.h"

typedef struct _bodyData {

} bodyData_t;

gameObject_t* createBody(playerData_t* player, vec_t pos);

#endif //ZOMBOID2_OBJ_ENEMY_BODY_H
