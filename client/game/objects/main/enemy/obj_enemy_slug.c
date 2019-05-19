//
// Created by maxim on 5/16/19.
//

#include "obj_enemy_slug.h"

int winH;
void slug_update(gameObject_t* this, void* data)
{
    slugData_t* sd = this->data;

    if(sd->hp > 0)
    {
        this->angle = twoPointsAngle(this->pos, sd->pd->pos);
        int frame = getFrame();
        this->pos.x += cos(this->angle) * sd->speed * (fabs(cos(frame / 15.0)) + 0.2);
        this->pos.y += sin(this->angle) * sd->speed * (fabs(cos(frame / 15.0)) + 0.2);

        if (frame % 10 == 0)
        {
            srfDrawTexture(texmGetID(TEXID_BLOOD_SLUGEMARK), randBool(),
                           color(1, 1, 1, 1), vec_add(this->pos, randVector(5, 5)), randAngle(), randRange(0.4, 0.5));
        }
    }
    else
    {
        this->frame = (int) (sd->frame += SLUG_DEAD_ANSPEED);
        if (this->frame >= this->cachedTex->framesCount)
        {
            for(int i = 0; i < SLUG_DEAD_MSB; i++)
                if(randBool())
                    scmPushObject(createMovingBloodSpawner(this->pos, randAngle(),
                            SLUG_DEAD_MSB_SPEED, SLUG_DEAD_MSB_TTL, SLUG_DEAD_MSB_COUNT, SLUG_DEAD_MSB_RANGE));
                else
                    scmPushObject(createMovingSlugSpawner(this->pos, randAngle(),
                            SLUG_DEAD_MSB_SPEED, SLUG_DEAD_MSB_TTL, SLUG_DEAD_MSB_COUNT, SLUG_DEAD_MSB_RANGE));

            spawnSpotBlood(ZOMBIE_DEAD_COUNT, ZOMBIE_DEAD_RANGE, this->pos);
            srfDrawTexture(texmGetID(TEXID_SLUG_DEAD), 3, color(1, 1, 1, 1), this->pos,
                    twoPointsAngle(vec(this->pos.x, winH - this->pos.y),
                                   vec(sd->pd->pos.x, winH - sd->pd->pos.y)),
                    1);
            scmDestroyObject(this, true);
        }
    }
}

void slug_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, slug_update);
}

int enemy_slug_harm(double damage, gameObject_t* this)
{
    slugData_t* sd = this->data;
    sd->hp -= damage;

    if(sd->hp <= 0) {
        this->texID = TEXID_SLUG_DEAD;
        this->frame = 1;
        this->animationSpeed = 0;
        this->cachedTex = texmGetID(this->texID);
        return 1;
    }

    return 0;
}

gameObject_t* createSlug(playerData_t* player, vec_t pos)
{
    gameObject_t* this = object();
    this->drawable = 1;
    this->texID = TEXID_ENEMY_SLUG;
    this->onInit = slug_init;
    this->pos = pos;
    this->ID = OBJECT_SLUG;
    this->animationSpeed = SLUG_ANSPEED;

    allocData(slugData_t, this, data);
    data->speed = randRange(SLUG_SPEED_MIN, SLUG_SPEED_MAX);
    data->hp = SLUG_HP;
    data->pd = player;
    data->frame = 0;

    return this;
}