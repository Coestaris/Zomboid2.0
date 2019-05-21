//
// Created by maxim on 5/13/19.
//

#ifndef ZOMBOID2_SCORE_H
#define ZOMBOID2_SCORE_H

#include "../objectInclude.h"

#include "main/enemy/obj_enemy_tic.h"
#include "main/enemy/obj_enemy_body.h"
#include "main/enemy/obj_enemy_zombie.h"
#include "main/enemy/obj_enemy_slug.h"
#include "main/enemy/obj_enemy_ghost.h"
#include "main/enemy/obj_enemy_slicer.h"

#define MAX_LEVELS 13
#define MAX_ENEMIES 6
#define COMPLETED 0.9

typedef struct _gameMobData {
    int wave;
    int toSpawn[MAX_ENEMIES];

    playerData_t* pd;
    long long lastSpawnFrame;
    int currentMobs;

} gameMobData_t;

int shouldSpawnMob(gameMobData_t* md);
double getKilledPercentage(gameMobData_t* md);
int killEnemy(int id);
double getMobSpawnInterval(int level);
int getMaxMobs(int level);
void increaseLevel(gameMobData_t* md);
gameMobData_t* createMobData();
void spawnEnemy(gameMobData_t* md);
int mobCount(int level);
void recieveScore(int level, int id);

#endif //ZOMBOID2_SCORE_H
