//
// Created by maxim on 1/24/19.
//

#include "obj_bullet.h"

void bullet_event_update(gameObject *object, void *data)
{
    int winW, winH;
    getWinSize(&winW, &winH);

    if( object->x < - object->cachedTex->width * object->size ||
        object->x > winW + object->cachedTex->width * object->size ||
        object->y < - object->cachedTex->height * object->size ||
        object->y > winH + object->cachedTex->height * object->size)
    {
        destroyObject(object, true);
    }
    else
    {
        object->x += cos(object->angle) * BULLET_SPEED;
        object->y += sin(object->angle) * BULLET_SPEED;
    }
}

void bullet_init(gameObject* object)
{
    subscribeEvent(object, EVT_Update, bullet_event_update);
}

gameObject* createBullet(double x, double y, double dirx, double diry)
{
    gameObject* go = object();
    go->drawable = true;

    go->x = x;
    go->y = y;
    go->angle = toPointsAngle(x, y, dirx, diry) + toRad(random() % 180 - 90);
    go->texID = TEXID_BULLET;
    go->size = 0.1;
    go->init = bullet_init;

    return go;
}
