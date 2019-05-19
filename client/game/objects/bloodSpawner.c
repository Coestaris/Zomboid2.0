//
// Created by maxim on 5/4/19.
//

#include "bloodSpawner.h"

tex_t* bloodTex;
tex_t* slugTex;

void spawnSpotBlood(int count, double range, vec_t position)
{
    for (size_t i = 0; i < count; i++)
    {
        srfDrawTexture(
                bloodTex, randIntRange(0, bloodTex->framesCount - 1), color(1, 1, 1, 1),
                vec_add(position, vec(randRange(-range, range), randRange(-range, range))),
                randAngle(), randRange(0.9, 1.1));
    }
}

void spawnSpotSlug(int count, double range, vec_t position)
{
    for (size_t i = 0; i < count; i++)
    {
        srfDrawTexture(
                slugTex, randIntRange(0, slugTex->framesCount - 1), color(1, 1, 1, 1),
                vec_add(position, vec(randRange(-range, range), randRange(-range, range))),
                randAngle(), randRange(0.9, 1.1));
    }
}

void bloodSpawnerInit(void)
{
    bloodTex = texmGetID(TEXID_BLOOD);
    slugTex = texmGetID(TEXID_BLOOD_SLUGEMARK);
}

void mbs_update(gameObject_t* this, void* data)
{
    movingBS_data_t* mbs = this->data;
    this->pos.x += mbs->xOffset;
    this->pos.y += mbs->yOffset;

    if(mbs->slug)
        spawnSpotSlug(mbs->bloodCount, mbs->bloodRange, this->pos);
    else
        spawnSpotBlood(mbs->bloodCount, mbs->bloodRange, this->pos);

    if(getFrame() - mbs->spawnTime > mbs->lifeTime) {
        scmDestroyObject(this, true);
    }
}


void mbs_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, mbs_update);
}

gameObject_t* createMovingSlugSpawner(vec_t pos, double angle, double speed, long long int ttl, int count, double range)
{
    gameObject_t* obj = createMovingBloodSpawner(pos, angle, speed, ttl, count, range);
    ((movingBS_data_t*)obj->data)->slug = 1;
    return obj;
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
    data->slug = 0;
    data->bloodCount = count;
    data->bloodRange = range;

    data->xOffset = cos(obj->angle) * data->speed;
    data->yOffset = sin(obj->angle) * data->speed;

    return obj;
}