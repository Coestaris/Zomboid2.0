//
// Created by maxim on 1/24/19.
//

#include "obj_bullet.h"

void bullet_event_update(gameObject_t* object, void* data)
{
    bulletData_t* bd = object->data;

    if (isInWindowExtendedRect(object, 100, 100))
    {
        if(bd->light) scmDestroyObject(bd->light, true);
        scmDestroyObject(object, true);
    }
    else
    {
        object->pos.x += bd->xOffset;
        object->pos.y += bd->yOffset;
        if(bd->light) bd->light->pos = object->pos;
    }
}

void bullet_box(gameObject_t* this, gameObject_t* box)
{
    bulletData_t* bd = this->data;
    if(bd->light) scmDestroyObject(bd->light, true);
    scmDestroyObject(this, true);
}

void bullet_zombie(gameObject_t* this, gameObject_t* zombie)
{
    bulletData_t* bd = this->data;
    scmPushObject(createMovingBloodSpawner(this->pos, this->angle,
            ZOMBIE_MBS_SPEED, ZOMBIE_MBS_TTL, ZOMBIE_MBS_COUNT, ZOMBIE_MBS_RANGE));
    if(enemy_zombie_harm(bd->damage, zombie)) { killEnemy(3); }

    if(this->texID == TEXID_BULLET_ROCKET)
    {
        scmPushObject(createExplosion(this->pos));
    }

    if(bd->light) scmDestroyObject(bd->light, true);
    scmDestroyObject(this, true);
}

void bullet_tic(gameObject_t* this, gameObject_t* tic)
{
    bulletData_t* bd = this->data;
    scmPushObject(createMovingBloodSpawner(this->pos, this->angle,
           TIC_MBS_SPEED, TIC_MBS_TTL, TIC_MBS_COUNT, TIC_MBS_RANGE));
    if(enemy_tic_harm(bd->damage, tic)) { killEnemy(1); }

    if(this->texID == TEXID_BULLET_ROCKET)
    {
        scmPushObject(createExplosion(this->pos));
    }

    if(bd->light) scmDestroyObject(bd->light, true);
    scmDestroyObject(this, true);
}

void bullet_body(gameObject_t* this, gameObject_t* body)
{
    bulletData_t* bd = this->data;
    scmPushObject(createMovingBloodSpawner(this->pos, this->angle,
           BODY_MBS_SPEED, BODY_MBS_TTL, BODY_MBS_COUNT, BODY_MBS_RANGE));
    if(enemy_body_harm(bd->damage, body)) { killEnemy(2);  }

    if(this->texID == TEXID_BULLET_ROCKET)
    {
        scmPushObject(createExplosion(this->pos));
    }

    if(bd->light) scmDestroyObject(bd->light, true);
    scmDestroyObject(this, true);
}

void bullet_slug(gameObject_t* this, gameObject_t* slug)
{
    bulletData_t* bd = this->data;
    scmPushObject(createMovingSlugSpawner(this->pos, this->angle,
           SLUG_MBS_SPEED, SLUG_MBS_TTL, SLUG_MBS_COUNT, SLUG_MBS_RANGE));
    spawnSpotBlood(SLUG_DEAD_COUNT / 2.5, SLUG_DEAD_RANGE / 2.5, slug->pos);
    if(enemy_slug_harm(bd->damage, slug)) { killEnemy(4);  }

    if(this->texID == TEXID_BULLET_ROCKET)
    {
        scmPushObject(createExplosion(this->pos));
    }

    if(bd->light) scmDestroyObject(bd->light, true);
    scmDestroyObject(this, true);
}

void bullet_ghost(gameObject_t* this, gameObject_t* body)
{
    bulletData_t* bd = this->data;
    if(this->texID == TEXID_BULLET_BOLT)
    {
        scmPushObject(createMovingBloodSpawner(this->pos, this->angle,
                                               GHOST_MBS_SPEED, GHOST_MBS_TTL, GHOST_MBS_COUNT, GHOST_MBS_RANGE));
        if (enemy_ghost_harm(bd->damage, body))
        { killEnemy(5); }

        if(bd->light) scmDestroyObject(bd->light, true);
        scmDestroyObject(this, true);
    }
}

void bullet_slicer(gameObject_t* this, gameObject_t* body)
{
    bulletData_t* bd = this->data;
    scmPushObject(createMovingBloodSpawner(this->pos, this->angle,
            SLICER_MBS_SPEED, SLICER_MBS_TTL, SLICER_MBS_COUNT, SLICER_MBS_RANGE));
    if(enemy_slicer_harm(bd->damage, body)) { killEnemy(6);  }

    if(this->texID == TEXID_BULLET_ROCKET)
    {
        scmPushObject(createExplosion(this->pos));
    }

    if(bd->light)  scmDestroyObject(bd->light, true);
    scmDestroyObject(this, true);
}

void bullet_init(gameObject_t* object)
{
    evqSubscribeEvent(object, EVT_Update, bullet_event_update);
    evqSubscribeCollisionEvent(object, OBJECT_BOX, bullet_box);

    evqSubscribeCollisionEvent(object, OBJECT_TIC,     bullet_tic);
    evqSubscribeCollisionEvent(object, OBJECT_BODY,    bullet_body);
    evqSubscribeCollisionEvent(object, OBJECT_ZOMBIE,  bullet_zombie);
    evqSubscribeCollisionEvent(object, OBJECT_SLUG,    bullet_slug);
    evqSubscribeCollisionEvent(object, OBJECT_GHOST,   bullet_ghost);
    evqSubscribeCollisionEvent(object, OBJECT_SLICER,  bullet_slicer);
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

    if(texID != TEXID_BULLET_BOLT)
    {
        bd->light = createLight(p, TEXID_LIGHT, 0.8, 0.03);
        scmPushObject(bd->light);
    } else
    {
        bd->light = NULL;
    }

    bd->xOffset = cos(go->angle) * BULLET_SPEED;
    bd->yOffset = sin(go->angle) * BULLET_SPEED;
    bd->damage = damage;
    bd->md = md;

    //scmPushObject(light);
    return go;
}
