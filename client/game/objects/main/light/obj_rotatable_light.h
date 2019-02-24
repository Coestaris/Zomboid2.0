//
// Created by maxim on 2/8/19.
//

#include "../../../objectInclude.h"

#ifndef ZOMBOID2_OBJ_ROTATABLE_LIGHT_H
#define ZOMBOID2_OBJ_ROTATABLE_LIGHT_H

typedef struct {
    gameObject* obj;
    double speed;

} rotatableLight_data ;

void rotatableLight_update(gameObject* this, void* data);
void rotatableLight_init(gameObject* this);
gameObject* create_rotatableLight(vec_t pos, double speed, gameObject* light);

#endif //ZOMBOID2_OBJ_ROTATABLE_LIGHT_H
