//
// Created by maxim on 5/13/19.
//

#include "score.h"

int levels[MAX_LEVELS * MAX_ENEMIES] = {
    //  tic     body    zombie  slug    ghost   slicer
        10,     5,      0,      0,      0,      0,
        10,     10,     0,      0,      0,      0,
        10,     10,     5,      0,      0,      0,
        10,     5,     10,      0,      0,      0,
        10,     5,     20,      5,      0,      0,
        10,     0,     20,     10,      0,      0,
        10,     0,     30,     10,      5,      0,
        15,     0,     30,     10,     10,      0,
        15,     0,     30,     10,     15,      0,
        15,     0,     30,     10,     20,      0,
        15,     0,     30,     10,     20,      5,
        15,     0,     30,     10,     20,     10,
        15,     5,     35,     30,     30,     20,
};

double maxMobs[MAX_LEVELS * 2] = {
    //Max mobs   |  spawn timeout
        5,          80,
        10,         60,
        15,         60,
        20,         60,
        20,         45,
        25,         45,
        25,         45,
        30,         30,
        35,         30,
        40,         30,
        45,         30,
        45,         30,
        50,         15,
};

double getMobSpawnInterval(int level)
{
    return maxMobs[level * 2 + 1];
}

int getMaxMobs(int level)
{
    return (int)maxMobs[level * 2];
}

int winW, winH;
gameObject_t* getMob(int id, playerData_t* pd)
{
    int dir = (int) randRange(0, 4);
    vec_t pos = vec(0, 0);
    double angle = 0;

    switch (dir)
    {
        case 0: //from top edge
            pos = vec(randRange(0, winW), 0);
            angle = randRange(M_PI_4, M_PI - M_PI_4);
            break;
        case 1: //from right edge
            pos = vec(winW, randRange(0, winH));
            angle = randRange(M_PI_2 + M_PI_4, 3 * M_PI_2 - M_PI_4);
            break;
        case 2: //from bottom edge
            pos = vec(randRange(0, winW), winH);
            angle = randRange(M_PI_4 + M_PI, 2 * M_PI - M_PI_4);
            break;
        case 3: //from left edge
            pos = vec(0, randRange(0, winH));
            angle = randRange(M_PI_4 - M_PI_2, M_PI - M_PI_4 - M_PI_2);
            break;
    }

    switch(id)
    {
        case 0:
            return createTic(pd, pos, angle);
        case 1:
            return createBody(pd, pos);
        case 2:
            return createZombie(pd, pos);
        case 3:
        case 4:
        case 5:
            return NULL;

        default:
            assert(0);
    }
}

int shouldSpawnMob(gameMobData_t* md)
{
    if(getKilledPercentage(md) == 1) {
        increaseLevel(md);
        return true;
    }

    return md->currentMobs < getMaxMobs(md->wave);
}

double getKilledPercentage(gameMobData_t* md)
{
    int sum1 = 0, sum2 = 0;
    for(int i = 1; i < MAX_ENEMIES; i++)
    {
        sum1 += md->toSpawn[i];
        sum2 += levels[md->wave * MAX_ENEMIES + i];
    }

    double v = (sum1 + md->currentMobs) * (2 - COMPLETED) / sum2;
    return 1 - (v > 1 ? 1 : v);
}

int ticCount;
int killEnemy(gameMobData_t* md, int id)
{
    if(id == 1)
        ticCount--;
    else
    {
        if (md->currentMobs != 0)
            md->currentMobs -= 1;
    }
}

void spawnEnemy(gameMobData_t* md)
{
    if(ticCount != levels[md->wave * MAX_ENEMIES])
    {
        scmPushObject(getMob(0, md->pd));
        ticCount++;
        printf("Spawned tic. Tic count %i\n", ticCount);
    }
    else
    {
        int sum = 0;
        for (int i = 1; i < MAX_ENEMIES; i++)
            sum += md->toSpawn[i];

        if (sum == 0)
            return;

        int index = randIntRange(0, sum);
        int i = 1;
        while (index - md->toSpawn[i] > 0)
            index -= md->toSpawn[i++];

        md->toSpawn[i] -= 1;
        md->currentMobs++;

        printf("Spawned mob %i. To spawn: %i\n", i, sum);

        scmPushObject(getMob(i, md->pd));
    }
}

void increaseLevel(gameMobData_t* md)
{
    md->wave += 1;
    for(int i = 0; i < MAX_ENEMIES; i++)
        md->toSpawn[i] = levels[md->wave * MAX_ENEMIES + i];
}

gameMobData_t* createMobData()
{
    gameMobData_t* md = malloc(sizeof(gameMobData_t));
    md->wave = 0;
    md->currentMobs = 0;
    md->lastSpawnFrame = 0;
    increaseLevel(md);
    return md;
}

int mobCount(int level)
{
    int sum = 0;
    for(int i = 0; i < MAX_ENEMIES; i++) {
        sum += levels[level * MAX_ENEMIES + i];
    }
    return sum;
}

void recieveScore(int level, int id)
{

}