//
// Created by maxim on 1/29/19.
//

#include "obj_enemy.h"

void enemy_event_update(gameObject_t *this, void *data)
{
    enemyData_t* ed = this->data;
    this->angle = twoPointsAngle(this->pos, ed->player->pos);

    //this->x += cos(this->angle) * ed->speed;
    //this->y += sin(this->angle) * ed->speed;

    if(ed->larm) {
        dqnDrawSprite(ed->larm_tex, color(1, 1, 1, 1), 0, this->pos, this->angle, this->size, 0);
    }

    if(ed->rarm) {
        dqnDrawSprite(ed->rarm_tex, color(1, 1, 1, 1), 0, this->pos, this->angle, this->size, 0);
    }
}

void enemy_init(gameObject_t* this)
{
    enemyData_t* ed = this->data;
    ed->larm_tex = texmGetID(TEXID_ENEMY_LARM);
    ed->rarm_tex = texmGetID(TEXID_ENEMY_RARM);

    evqSubscribeEvent(this, EVT_Update, enemy_event_update);
}

gameObject_t *createEnemy(gameObject_t* player, vec_t pos) {
    gameObject_t* obj = object();
    obj->drawable = 1;
    obj->texID = TEXID_ENEMY;
    obj->frame = (int)randRange(0, texmGetID(obj->texID)->framesCount);

    obj->size = 10;
    obj->pos = pos;

    obj->onInit = enemy_init;

    obj->data = malloc(sizeof(enemyData_t));
    enemyData_t* ed = obj->data;
    ed->player = player;
    ed->speed = randRange(ENEMY_SPEED_MIN, ENEMY_SPEED_MAX);

    ed->larm = true;
    ed->rarm = true;

    return obj;
}


