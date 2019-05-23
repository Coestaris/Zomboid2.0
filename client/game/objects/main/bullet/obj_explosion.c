//
// Created by maxim on 5/13/19.
//

#include "obj_explosion.h"

#define EXPLOSION_MIN_DMG 20
#define EXPLOSION_MAX_DMG 25

void exposion_update(gameObject_t* this, void* data)
{
    explosionData_t* ed = this->data;

    ed->frame += 0.5;
    this->size += 0.1;
    this->frame = (int)ed->frame;

    int objectCount = 0;
    gameObject_t** objects = scmGetObjects(&objectCount);

    for(int i = 0; i < objectCount; i++)
    {
        if (objects[i]->ID == OBJECT_ZOMBIE || objects[i]->ID == OBJECT_TIC || objects[i]->ID == OBJECT_SLUG ||
            objects[i]->ID == OBJECT_BODY || objects[i]->ID == OBJECT_SLICER)
        {

            if(distance(this->pos, objects[i]->pos) < 120)
            {
                switch (objects[i]->ID)
                {
                    case OBJECT_TIC:
                        enemy_tic_harm(randRange(EXPLOSION_MIN_DMG, EXPLOSION_MAX_DMG), objects[i]);
                        break;
                    case OBJECT_BODY:
                        enemy_body_harm(randRange(EXPLOSION_MIN_DMG, EXPLOSION_MAX_DMG), objects[i]);
                        break;
                    case OBJECT_ZOMBIE:
                        enemy_zombie_harm(randRange(EXPLOSION_MIN_DMG, EXPLOSION_MAX_DMG), objects[i]);
                        break;
                    case OBJECT_SLUG:
                        enemy_slug_harm(randRange(EXPLOSION_MIN_DMG, EXPLOSION_MAX_DMG), objects[i]);
                        break;
                    case OBJECT_GHOST:
                        enemy_ghost_harm(randRange(EXPLOSION_MIN_DMG, EXPLOSION_MAX_DMG), objects[i]);
                        break;
                    case OBJECT_SLICER:
                        enemy_slicer_harm(randRange(EXPLOSION_MIN_DMG, EXPLOSION_MAX_DMG), objects[i]);
                        break;
                    default:
                        break;
                }
            }

            scmPushObject(createMovingBloodSpawner(this->pos, randAngle(),
                     ZOMBIE_MBS_SPEED, ZOMBIE_MBS_TTL + randRange(-2, 2) - 2, ZOMBIE_MBS_COUNT - 1, ZOMBIE_MBS_RANGE));
        }
    }

    if(this->cachedTex && this->frame == this->cachedTex->framesCount) {
        scmDestroyObject(this, true);
    }
}

void explosion_update(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, exposion_update);
}

gameObject_t* createExplosion(vec_t pos)
{
    gameObject_t* this = object();
    this->drawable = 1;
    this->texID = TEXID_EXPLOSION;
    this->animationSpeed = 0;
    this->size = 1;
    this->onInit = explosion_update;
    this->pos = pos;

    allocData(explosionData_t, this, data);
    data->frame = 0;

    return this;
}