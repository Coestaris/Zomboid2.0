//
// Created by maxim on 1/24/19.
//

#include "obj_bullet.h"

void bullet_event_update(gameObject_t* object, void* data)
{
    int objectsCount;
    bulletData_t* bd = object->data;

    gameObject_t** objects = scmGetObjects(&objectsCount);
    gameObject_t* light = bd->light;

    if (isInWindowExtendedRect(object, BULLET_LIGHT_SIZE, BULLET_LIGHT_SIZE))
    {
        scmDestroyObject(light, true);
        scmDestroyObject(object, true);
    }
    else
    {
        object->pos.x += bd->xOffset;
        object->pos.y += bd->yOffset;
        //light->pos = object->pos;
    }
}

void bullet_box(gameObject_t* this, gameObject_t* box)
{
    bulletData_t* bd = this->data;
    scmDestroyObject(bd->light, true);
    scmDestroyObject(this, true);
}

void bullet_zombie(gameObject_t* this, gameObject_t* zombie)
{
    bulletData_t* bd = this->data;
    scmPushObject(createMovingBloodSpawner(this->pos, this->angle, 14, 5, 2, 9));
    scmDestroyObject(this, true);

    if(enemy_zombie_harm(bd->damage, zombie))
    {
        killEnemy(bd->md, 3);
    }
}

void bullet_tic(gameObject_t* this, gameObject_t* tic)
{
    bulletData_t* bd = this->data;
    scmPushObject(createMovingBloodSpawner(this->pos, this->angle, 14, 5, 2, 9));
    scmDestroyObject(this, true);
    enemy_tic_harm(bd->damage, tic);
}

void bullet_init(gameObject_t* object)
{
    evqSubscribeEvent(object, EVT_Update, bullet_event_update);
    evqSubscribeCollisionEvent(object, OBJECT_BOX, bullet_box);
    evqSubscribeCollisionEvent(object, OBJECT_ZOMBIE, bullet_zombie);
    evqSubscribeCollisionEvent(object, OBJECT_TIC, bullet_tic);
}

gameObject_t* createBullet(gameMobData_t* md, vec_t p, double angle, int texID, double damage)
{
    gameObject_t* go = object();
    go->drawable = true;

    go->depth = 1;
    go->pos = p;

    go->angle = angle;
    go->texID = texID;
    go->size = 1;
    go->onInit = bullet_init;
    go->data = malloc(sizeof(bulletData_t));

  /*  gameObject_t* light = createTexturedAreaLT(p, BULLET_LIGHT_SIZE, color(randRange(0, 1), randRange(0, 1), randRange(0, 1),
                                                     BULLET_LIGHT_ALPHA), texmGetID(TEXID_LIGHT), 0);*/
    bulletData_t* bd = go->data;

    go->animationSpeed = 1;

   // bd->light = light;
    bd->xOffset = cos(go->angle) * BULLET_SPEED;
    bd->yOffset = sin(go->angle) * BULLET_SPEED;
    bd->damage = damage;
    bd->md = md;

    //scmPushObject(light);
    return go;
}
