//
// Created by maxim on 2/8/19.
//

#include "../../../objectInclude.h"

#ifndef ZOMBOID2_OBJ_ROTATABLE_LIGHT_H
#define ZOMBOID2_OBJ_ROTATABLE_LIGHT_H

typedef struct _rotatableLight_data
{
    gameObject_t* obj;
    double speed;

} rotatableLight_data_t;

gameObject_t* create_rotatableLight(vec_t pos, double speed, gameObject_t* light);

#endif //ZOMBOID2_OBJ_ROTATABLE_LIGHT_H
