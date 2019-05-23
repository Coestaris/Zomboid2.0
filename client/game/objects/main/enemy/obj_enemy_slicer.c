//
// Created by maxim on 5/16/19.
//

#include "obj_enemy_slicer.h"

void slicer_update(gameObject_t* this, void* data)
{
    slicerData_t* sd = this->data;

    if(sd->hp > 0)
    {
        this->angle = twoPointsAngle(this->pos, sd->pd->pos);
        this->pos.x += cos(this->angle) * sd->speed;
        this->pos.y += sin(this->angle) * sd->speed;
        long long frame = getFrame();

        double a = fabs(cos(frame / 25.0)) - 0.2;
        this->alpha = a > 0.5 ? a : 0.1;
        sd->speed = SLICER_SPEED * fabs(cos(frame / 25.0)) + SLICER_SPEED_MIN;
    }
    else
    {
        this->frame = (int)(sd->frame += ZOMBIE_DEAD_ANSPEED);
        if(this->frame >= this->cachedTex->framesCount) {
            for(int i = 0; i < ZOMBIE_DEAD_MSB; i++)
                scmPushObject(createMovingBloodSpawner(this->pos, randAngle(),
                                                       ZOMBIE_DEAD_MSB_SPEED, ZOMBIE_DEAD_MSB_TTL, ZOMBIE_DEAD_MSB_COUNT, ZOMBIE_DEAD_MSB_RANGE));

            spawnSpotBlood(ZOMBIE_DEAD_COUNT, ZOMBIE_DEAD_RANGE, this->pos);
            srfDrawTexture(texmGetID(TEXID_BLOOD_DEAD), randBool(), color(1, 1, 1, 1), this->pos, randAngle(), randRange(0.8, 1.1));
            scmDestroyObject(this, true);
        }
    }
}

void slicer_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, slicer_update);
}


int enemy_slicer_harm(double damage, gameObject_t* this)
{
    slicerData_t* sd = this->data;
    sd->hp -= damage;

    if(sd->hp <= 0) {
        this->texID = randBool() ? TEXID_ZOMBIE_DEAD1 : TEXID_ZOMBIE_DEAD2;
        this->frame = 1;
        this->cachedTex = texmGetID(this->texID);
        return 1;
    }

    return 0;
}

gameObject_t* createSlicer(playerData_t* player, vec_t pos)
{
    gameObject_t* this = object();
    this->drawable = 1;
    this->texID = TEXID_ENEMY_SLICER;
    this->onInit = slicer_init;
    this->pos = pos;
    this->ID = OBJECT_SLICER;

    allocData(slicerData_t, this, data);
    data->speed = SLICER_SPEED_MIN;
    data->hp = SLICER_HP;
    data->pd = player;

    return this;
}