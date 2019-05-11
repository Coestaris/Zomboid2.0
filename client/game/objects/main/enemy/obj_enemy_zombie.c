//
// Created by maxim on 1/29/19.
//

#include "obj_enemy_zombie.h"

void enemy_event_update(gameObject_t* this, void* data)
{
    enemyData_t* ed = this->data;
    this->angle = twoPointsAngle(this->pos, ed->player->pos);

    this->pos.x += cos(this->angle) * ed->speed;
    this->pos.y += sin(this->angle) * ed->speed;
}

void enemy_zombie_harm(gameObject_t* this)
{
    enemyData_t* ed = this->data;
    ed->hp -= randRange(5, 30);

    if(ed->hp < 2 * ENEMY_HP / 3.0) this->frame = ed->larm ? 1 : 2;
    if(ed->hp < ENEMY_HP / 3.0) this->frame = 3;
    if(ed->hp <= 0) {
        scmDestroyObject(this, true);
        spawnSpotBlood(20, 30, this->pos);
    }
}

void enemy_init(gameObject_t* this)
{
    enemyData_t* ed = this->data;
    ed->larm_tex = texmGetID(TEXID_ENEMY_LARM);
    ed->rarm_tex = texmGetID(TEXID_ENEMY_RARM);

    evqSubscribeEvent(this, EVT_Update, enemy_event_update);
//    evqSubscribeCollisionEvent(this, TEXID_BULLET, enemy_event_bulletCollision);
}

gameObject_t* createEnemy(playerData_t* player, vec_t pos)
{
    gameObject_t* obj = object();
    obj->drawable = 1;
    obj->texID = randIntRange(TEXID_ENEMY_ZOMBIE_1, TEXID_ENEMY_ZOMBIE_3);
    obj->frame = 0;
    obj->ID = OBJECT_ZOMBIE;

    obj->size = 1;
    obj->pos = pos;

    obj->onInit = enemy_init;

    obj->data = malloc(sizeof(enemyData_t));
    enemyData_t* ed = obj->data;
    ed->player = player;
    ed->hp = ENEMY_HP;
    ed->speed = randRange(ENEMY_SPEED_MIN, ENEMY_SPEED_MAX);

    ed->larm = randBool();

    return obj;
}


