//
// Created by maxim on 5/4/19.
//

#ifndef ZOMBOID2_OBJECT_MENU_BEETLE_H
#define ZOMBOID2_OBJECT_MENU_BEETLE_H

#include "../../objectInclude.h"

#include "../bloodSpawner.h"

#define MBEETLE_ROOM_OFFSET 30
#define MBEETLE_BLOOD_COUNT 10
#define MBEETLE_BLOOD_RANGE 10

typedef struct _mbeetleData
{
    double xOffset;
    double yOffset;

} mbeetleData_t;

gameObject_t* createMenuBeetle(vec_t pos, double angle, double speed);

#endif //ZOMBOID2_OBJECT_MENU_BEETLE_H
