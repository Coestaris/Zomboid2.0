//
// Created by maxim on 1/23/19.
//

#include "obj_player.h"

void player_init(gameObject* object)
{
    subscribeEvent(object, EVT_MouseMove, player_event_mouseMove);
    subscribeEvent(object, EVT_MouseClick, player_event_mouseClick);
    puts("Player created!");
}

void player_event_mouseMove(gameObject *object, void *data)
{
    mouseEvent* me = data;
    object->x = me->x;
    object->y = me->y;
}

gameObject* createPlayer()
{
    gameObject* go = malloc(sizeof(gameObject));
    go->drawable = 1;

    go->texID = 2;
    go->size = 1;
    go->init = player_init;
    return go;
}

void player_event_mouseClick(gameObject *object, void *data)
{
    mouseEvent* me = data;
    if(me->mouse == MB_LEFT && me->state == MS_PRESSED)
    {
        object->size *= 1.1;
    }
    else if(me->mouse == MB_RIGHT && me->state == MS_PRESSED)
    {
        object->size *= 0.9;
    }
}
