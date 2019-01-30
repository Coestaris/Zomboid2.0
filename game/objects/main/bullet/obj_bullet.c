//
// Created by maxim on 1/24/19.
//

#include "obj_bullet.h"

void bullet_event_update(gameObject *object, void *data)
{
    int objectsCount;
    bulletData* bd = object->data;

    gameObject** objects = scmGetObjects(&objectsCount);
    gameObject* light = bd->light;

    for(int i = 0; i < objectsCount; i++)
    {
        if(objects[i]->texID == TEXID_BOX)
        {
            double boxX = objects[i]->x;
            double boxY = objects[i]->y;
            double boxW = objects[i]->cachedTex->width * objects[i]->size;
            double boxH = objects[i]->cachedTex->height * objects[i]->size;

            if(object->x > boxX - boxW / 2 &&
               object->x < boxX + boxW / 2 &&
               object->y > boxY - boxH / 2 &&
               object->y < boxY + boxH / 2)
            {
                scmDestroyObject(light, true);
                scmDestroyObject(object, true);
                return;
            }
        }
    }

    if(isInWindowRect(object))
    {
        scmDestroyObject(light, true);
        scmDestroyObject(object, true);
    }
    else
    {
        object->x += bd->xOffset;
        object->y += bd->yOffset;
        light->x = object->x;
        light->y = object->y;
    }
}

void bullet_init(gameObject* object)
{
    evqSubscribeEvent(object, EVT_Update, bullet_event_update);
}

gameObject* createBullet(double x, double y, double dirx, double diry)
{
    gameObject* go = object();
    go->drawable = true;

    go->depth = 2;
    go->x = x;
    go->y = y;
    go->angle = twoPointsAngle(x, y, dirx, diry) + toRad(randRange(-50, 50));
    go->texID = TEXID_BULLET;
    go->size = 1;
    go->onInit = bullet_init;

    go->data = malloc(sizeof(bulletData));

    gameObject* light = createLight(x, y, BULLET_LIGHT_SIZE, BULLET_LIGHT_ALPHA);
    bulletData* bd = go->data;

    bd->light = light;
    bd->xOffset = cos(go->angle) * BULLET_SPEED;
    bd->yOffset = sin(go->angle) * BULLET_SPEED;


    scmPushObject(light);
    return go;
}
