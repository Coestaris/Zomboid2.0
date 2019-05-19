//
// Created by maxim on 1/29/19.
//

#include "obj_enemy_zombie.h"

void enemy_event_update(gameObject_t* this, void* data)
{
    zombieData_t* ed = this->data;

    if(ed->hp >= 0)
    {
        this->angle = twoPointsAngle(this->pos, ed->player->pos);
        this->pos.x += cos(this->angle) * ed->speed;
        this->pos.y += sin(this->angle) * ed->speed;
    }
    else
    {
        this->frame = (int)(ed->frame += ZOMBIE_DEAD_ANSPEED);
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

int enemy_zombie_harm(double damage, gameObject_t* this)
{
    zombieData_t* ed = this->data;
    double lastHp = ed->hp;

    ed->hp -= damage;

    if(lastHp >= 2 * ZOMBIE_HP / 3.0 && ed->hp <= 2 * ZOMBIE_HP / 3.0)
    {
        this->frame = ed->larm ? 1 : 2;
        spawnSpotBlood(ZOMBIE_HARM_ARM1_COUNT, ZOMBIE_HARM_ARM1_RANGE, this->pos);
        srfDrawTexture(texmGetID(ed->larm ? TEXID_ENEMY_LARM : TEXID_ENEMY_RARM),
                       0, color(1, 1, 1, 1), this->pos, randAngle(), randRange(0.8, 1));
    }
    if(lastHp >= ZOMBIE_HP / 3.0 && ed->hp < ZOMBIE_HP / 3.0)
    {
        spawnSpotBlood(ZOMBIE_HARM_ARM2_COUNT, ZOMBIE_HARM_ARM2_RANGE, this->pos);
        srfDrawTexture(texmGetID((!ed->larm) ? TEXID_ENEMY_LARM : TEXID_ENEMY_RARM),
                       0, color(1, 1, 1, 1), this->pos, randAngle(), randRange(0.8, 1));
        this->frame = 3;
    }
    if(ed->hp <= 0) {
        this->texID = randBool() ? TEXID_ZOMBIE_DEAD1 : TEXID_ZOMBIE_DEAD2;
        this->frame = 1;
        this->cachedTex = texmGetID(this->texID);
        return 1;
    }

    return 0;
}

void enemy_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, enemy_event_update);
}

gameObject_t* createZombie(playerData_t* player, vec_t pos)
{
    gameObject_t* obj = object();
    obj->drawable = 1;
    obj->texID = randIntRange(TEXID_ENEMY_ZOMBIE_1, TEXID_ENEMY_ZOMBIE_3);
    obj->frame = 0;
    obj->ID = OBJECT_ZOMBIE;

    obj->size = 1;
    obj->pos = pos;

    obj->onInit = enemy_init;

    obj->data = malloc(sizeof(zombieData_t));
    zombieData_t* ed = obj->data;
    ed->player = player;
    ed->hp = ZOMBIE_HP;
    ed->speed = randRange(ZOMBIE_SPEED_MIN, ZOMBIE_SPEED_MAX);
    ed->frame = 0;
    ed->larm = randBool();

    return obj;
}


