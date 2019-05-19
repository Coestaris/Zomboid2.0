//
// Created by maxim on 5/4/19.
//

#ifndef ZOMBOID2_BLOODSPAWNER_H
#define ZOMBOID2_BLOODSPAWNER_H

#include "../objectInclude.h"

void bloodSpawnerInit(void);
void spawnSpotBlood(int count, double range, vec_t position);
void spawnSpotSlug(int count, double range, vec_t position);

typedef struct _movingBS_data{
    double speed;
    long long lifeTime;
    long long spawnTime;

    int bloodCount;
    double bloodRange;

    double xOffset;
    double yOffset;

    int slug;

} movingBS_data_t;

gameObject_t* createMovingSlugSpawner(vec_t pos, double angle, double speed, long long int ttl, int count, double range);
gameObject_t* createMovingBloodSpawner(vec_t pos, double angle, double speed, long long int ttl, int count, double range);

#endif //ZOMBOID2_BLOODSPAWNER_H
