//
// Created by maxim on 1/25/19.
//

#ifndef ZOMBOID2_OBJ_BOX_H
#define ZOMBOID2_OBJ_BOX_H

#include "../objectInclude.h"

void box_init(gameObject* object);
void box_event_update(gameObject *object, void *data);
gameObject* createBox(int x, int y);


#endif //ZOMBOID2_OBJ_BOX_H
