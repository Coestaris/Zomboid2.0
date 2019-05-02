//
// Created by maxim on 1/24/19.
//

#include "obj_bullet.h"

void bullet_event_update(gameObject_t *object, void *data)
{
    int objectsCount;
    bulletData_t* bd = object->data;

    gameObject_t** objects = scmGetObjects(&objectsCount);
    gameObject_t* light = bd->light;

    for(int i = 0; i < objectsCount; i++)
    {
        if(objects[i]->texID == TEXID_BOX)
        {
            double boxX = objects[i]->pos.x;
            double boxY = objects[i]->pos.y;
            double boxW = objects[i]->cachedTex->width * objects[i]->size;
            double boxH = objects[i]->cachedTex->height * objects[i]->size;

            if(object->pos.x > boxX - boxW / 2 &&
               object->pos.x < boxX + boxW / 2 &&
               object->pos.y > boxY - boxH / 2 &&
               object->pos.y < boxY + boxH / 2)
            {
                scmDestroyObject(light, true);
                scmDestroyObject(object, true);
                return;
            }
        }
    }

    if(isInWindowExtendedRect(object, BULLET_LIGHT_SIZE, BULLET_LIGHT_SIZE))
    {
        scmDestroyObject(light, true);
        scmDestroyObject(object, true);
    }
    else
    {
        object->pos.x += bd->xOffset;
        object->pos.y += bd->yOffset;
        light->pos = object->pos;
    }
}

void bullet_init(gameObject_t* object)
{
    evqSubscribeEvent(object, EVT_Update, bullet_event_update);
}

gameObject_t* createBullet(vec_t p, double angle)
{
    gameObject_t* go = object();
    go->drawable = true;

    go->depth = 2;
    go->pos = p;

    go->angle = angle + toRad(randRange(-50, 50));
    go->texID = TEXID_BULLET;
    go->size = 1;
    go->onInit = bullet_init;

    go->data = malloc(sizeof(bulletData_t));

    gameObject_t* light = createTexturedAreaLT(p, BULLET_LIGHT_SIZE,
            color(randRange(0, 1), randRange(0, 1), randRange(0, 1), BULLET_LIGHT_ALPHA), texmGetID(TEXID_LIGHT), 0);
    bulletData_t* bd = go->data;

    bd->light = light;
    bd->xOffset = cos(go->angle) * BULLET_SPEED;
    bd->yOffset = sin(go->angle) * BULLET_SPEED;


    scmPushObject(light);
    return go;
}
