//
// Created by maxim on 5/4/19.
//

#ifndef ZOMBOID2_OBJECT_BEETLE_SPAWNER_H
#define ZOMBOID2_OBJECT_BEETLE_SPAWNER_H

#include "../../objectInclude.h"
#include "object_menu_beetle.h"

#define BEETLE_SPAWN_RATE 30
#define BEETLE_SPEED 0.2

typedef struct _mbeetleSpawnerData
{
    long long lastSpawn;

} mbeetleSpawnerData_t;

gameObject_t* createMenuBeetleSpawner();

#endif //ZOMBOID2_OBJECT_BEETLE_SPAWNER_H
