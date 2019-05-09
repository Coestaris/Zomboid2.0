//
// Created by maxim on 5/4/19.
//

#include "bloodSpawner.h"

tex_t* bloodTex;

void spawnSpotBlood(int count, double range, vec_t position)
{
    for (size_t i = 0; i < count; i++)
    {
        srfDrawTexture(
                bloodTex, randIntRange(0, bloodTex->framesCount - 1), 1,
                vec_add(position, vec(randRange(-range, range), randRange(-range, range))),
                randBool(), randBool());
    }
}

void bloodSpawnerInit(void)
{
    bloodTex = texmGetID(TEXID_BLOOD);
}

void mbs_update(gameObject_t* this, void* data)
{
    movingBS_data_t* mbs = this->data;
    this->pos.x += cos(this->angle) * mbs->speed;
    this->pos.y += sin(this->angle) * mbs->speed;

    spawnSpotBlood(mbs->bloodCount, mbs->bloodRange, this->pos);

    if(getFrame() - mbs->spawnTime > mbs->lifeTime) {
        scmDestroyObject(this, true);
    }
}


void mbs_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, mbs_update);
}

gameObject_t* createMovingBloodSpawner(vec_t pos, double angle, double speed, long long int ttl, int count, double range)
{
    gameObject_t* obj = object();
    obj->angle = angle;
    obj->pos = pos;
    obj->onInit = mbs_init;

    obj->data = malloc(sizeof(movingBS_data_t));
    movingBS_data_t* data = obj->data;

    data->spawnTime = getFrame();
    data->lifeTime = ttl;
    data->speed = speed;
    data->bloodCount = count;
    data->bloodRange = range;

    return obj;
}