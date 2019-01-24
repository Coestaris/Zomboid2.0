//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_OBJ_TEST_H
#define ZOMBOID2_OBJ_TEST_H

#include "../../lib/gameobject.h"
#include "../../lib/eventQueue.h"

void player_init(gameObject* object);
void player_event_mouseMove(gameObject *object, void *data);
void player_event_mouseClick(gameObject *object, void *data);
gameObject* createPlayer();

#endif //ZOMBOID2_OBJ_TEST_H
