//
// Created by maxim on 1/23/19.
//

#include "obj_player.h"

void player_init(gameObject* object)
{
    subscribeEvent(object, EVT_MouseClick, player_event_mouseClick);
    puts("Player created!");
}

void player_event_mouseClick(gameObject* object, void* data)
{
    mouseEvent* me = data;
    printf("Player caught mouse. X: %i, Y: %i, B: %i, S: %i\n", me->x, me->y, me->mouse, me->state);
}

gameObject* createPlayer()
{
    gameObject* go = malloc(sizeof(gameObject));
    go->texID = 1;
    go->init = player_init;
    return go;
}
