//
// Created by maxim on 5/16/19.
//

#include "obj_enemy_ghost.h"

void ghost_update(gameObject_t* this, void* data)
{

}

void ghost_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_Update, ghost_update);
}

gameObject_t* createGhost(playerData_t* player, vec_t pos)
{
    gameObject_t* this = object();
    this->drawable = 1;
    this->texID = TEXID_ENEMY_GHOST;

    allocData(ghostData_t, this, data);

    return this;
}