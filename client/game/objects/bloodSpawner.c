//
// Created by maxim on 5/4/19.
//

#include "bloodSpawner.h"

tex_t* bloodTex;
void spawnSpotBlood(int count, double range, vec_t position)
{
    for(size_t i = 0; i < count; i++)
    {
        srfDrawTexture(
                bloodTex, (int)randRange(0, bloodTex->framesCount), 1,
                vec_add(position, vec(randRange(-range, range), randRange(-range, range))),
                rand() % 2, rand() % 2);
    }
}

void bloodSpawnerInit(void)
{
    bloodTex = texmGetID(TEXID_BLOOD);
}