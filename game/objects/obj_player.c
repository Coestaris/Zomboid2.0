//
// Created by maxim on 1/23/19.
//

#include "obj_player.h"

void player_init(gameObject* object)
{
    subscribeEvent(object, EVT_MouseClick, player_event_mouseClick);
    subscribeEvent(object, EVT_Update, player_event_update);
}

void player_event_update(gameObject *object, void *data)
{
    if(object->frame == 0) object->animationSpeed = 0;

    int mx, my;
    getMousePos(&mx, &my);
    object->angle = toPointsAngle(object->x, object->y, mx, my);

    if(keyPressed('a') || specKeyPressed(GLUT_KEY_LEFT))  object->x -= 2;
    if(keyPressed('w') || specKeyPressed(GLUT_KEY_UP))    object->y -= 2;
    if(keyPressed('s') || specKeyPressed(GLUT_KEY_DOWN))  object->y += 2;
    if(keyPressed('d') || specKeyPressed(GLUT_KEY_RIGHT)) object->x += 2;
}

gameObject* createPlayer()
{
    gameObject* go = object();
    go->drawable = true;

    go->x = 100;
    go->y = 200;

    go->depth = 1;
    go->texID = TEXID_PLAYER;
    go->animationSpeed = 0;
    go->size = 1;
    go->init = player_init;
    return go;
}

void player_event_mouseClick(gameObject *object, void *data)
{
    mouseEvent* me = data;
    if(me->mouse == MB_LEFT && me->state == MS_RELEASED) {
        object->frame = 1;
        object->animationSpeed = 2;

        double x, y;
        relativeCoordinates(&x, &y, object);

        pushObject(createBullet(x, y, me->x, me->y));
    }
}
