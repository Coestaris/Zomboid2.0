//
// Created by maxim on 1/24/19.
//

#include "loader.h"

void initPublicObjects(void)
{
    scmPushPublicObject(OBJECT_PLAYER, createPlayer);
    scmPushPublicObject(OBJECT_BOX, createBox);
}