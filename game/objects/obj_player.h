//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_OBJ_TEST_H
#define ZOMBOID2_OBJ_TEST_H

#include "../objectInclude.h"

#include "obj_bullet.h"

typedef struct {
    long long lastFireFrame;

} playerData;

void player_init(gameObject* object);
void player_event_update(gameObject *object, void *data);
gameObject* createPlayer();

#endif //ZOMBOID2_OBJ_TEST_H
