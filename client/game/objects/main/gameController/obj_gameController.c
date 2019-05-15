//
// Created by maxim on 5/11/19.
//

#include "obj_gameController.h"

int winW, winH;
void gc_update(gameObject_t* this, void* data)
{
    gameControllerData_t* gd = this->data;
    playerData_t* pd = gd->players[0];
    vec_t mpos = getMousePos();

    pd->angle = twoPointsAngle(pd->pos, mpos);
    if (keyPressed('a') || specKeyPressed(GLUT_KEY_LEFT)) pd->pos.x -= PLAYER_MOVE_X;
    if (keyPressed('w') || specKeyPressed(GLUT_KEY_UP)) pd->pos.y -= PLAYER_MOVE_Y;
    if (keyPressed('s') || specKeyPressed(GLUT_KEY_DOWN)) pd->pos.y += PLAYER_MOVE_X;
    if (keyPressed('d') || specKeyPressed(GLUT_KEY_RIGHT)) pd->pos.x += PLAYER_MOVE_Y;

    long long frame = getFrame();

    if(getWeaponAutoFire(pd->weapon)) {
        if(getMouseState(MB_LEFT) == MS_PRESSED &&  frame - pd->lastFireFrame > getWeaponFireRate(pd->weapon)) {
            pd->lastFireFrame = frame;
            fire(pd);
        }
    }

    if(getMouseState(MB_LEFT) == MS_PRESSED && pd->weapon == 4 && pd->weaponCount[pd->weapon] != 0) {
        proceedLaser(pd);
    }

    if( pd->state == shooting ) {
        if(pd->frame >= getPlayerTexture(pd->weapon)->framesCount - 1)
        {
            pd->state = nothing;
            if(pd->weapon == 5) {
                pd->frame = 3;
            } else if(pd->weapon == 1){
                pd->frame = 1;
            } else {
                pd->frame = 0;
            }
        }
        else
        {
            pd->frame += getWeaponShootingSpeed(pd->weapon);
        }
    }

    if(pd->state == reloading) {

        dqnDrawSprite(getPlayerReloadTexture(pd->weapon), color(1, 1, 1, 1), (int) pd->frame,
                      vec_sub(pd->pos, vec(pd->weapon == 5 ? 18 : 0, 0)), pd->angle, 1, 4);

        if(pd->frame >= getPlayerReloadTexture(pd->weapon)->framesCount - 1)
        {
            reload(pd);
            pd->state = nothing;
            pd->frame = 0;
        }
        else pd->frame += getWeaponReloadingSpeed(pd->weapon);

    } else
    {
        dqnDrawSprite(getPlayerTexture(pd->weapon), color(1, 1, 1, 1), (int) pd->frame,
                      vec_sub(pd->pos, vec(pd->weapon == 5 ? 18 : 0, 0)), pd->angle, 1, 4);
    }

}

void gc_mouse(gameObject_t* this, void* data)
{
    gameControllerData_t* gd = this->data;
    playerData_t* pd = gd->player;
    mouseEvent_t* me = data;
    if(me->mouse == MB_WHEEL_UP && me->state == MS_PRESSED)
    {
        pd->frame = 0;
        while(pd->weaponStates[(pd->weapon = (pd->weapon + 1) % WEAPON_COUNT)] == 0);
    }
    else if(me->mouse == MB_WHEEL_DOWN && me->state == MS_PRESSED)
    {
        pd->frame = 0;
        while(pd->weaponStates[(pd->weapon = ((pd->weapon - 1 < 0) ? WEAPON_COUNT - 1 : pd->weapon - 1))] == 0);
    }
    if(me->mouse == MB_LEFT && me->state == MS_PRESSED && !getWeaponAutoFire(pd->weapon))
    {
        fire(pd);
    }
}

void gc_keyPressed(gameObject_t* this, void* data)
{
    keyboardEvent_t* ke = data;
    gameControllerData_t* gd = this->data;
    playerData_t* pd = gd->player;

    if (ke->key == 'f')
    {
        glutFullScreenToggle();
    }
    else if (ke->key == 'e')
    {
        srfDrawTexture(texmGetID(TEXID_BOX), 0, 1, vec(100, 100), 0, 0);
    }
    else if (ke->key == 'c')
    {
        srfClear();
    }
    else if (ke->key == 'q')
    {
        scmPushObject(createEnemy(pd, vec(randRange(0, winW), randRange(0, winH))));
    }
    else if(ke->key >= '1' && ke->key <= '6')
    {
        if(pd->state != reloading)
        {
            int wtype = ke->key - '1';
            if (pd->weaponStates[wtype])
            {
                pd->frame = 0;
                pd->weapon = wtype;
            }
        }
    }
    else if(ke->key == 'r')
    {
        if(pd->weaponMaxCount[pd->weapon] != 0 && pd->weaponCount[pd->weapon] != getWeaponCount(pd->weapon))
            pd->state = reloading;
    }
    else if(ke->key == 't')
    {
        pd->weaponMaxCount[pd->weapon] = getWeaponMaxCount(pd->weapon);
        pd->weaponCount[pd->weapon] = getWeaponCount(pd->weapon);
    }
    else if(ke->key == 'g')
    {
        if(pd->grenades > 0) pd->grenades -= 1;
    }
    else if(ke->key == '`')
    {
        exit(0);
    }
}

void gc_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_MouseClick, gc_mouse);
    evqSubscribeEvent(this, EVT_Update, gc_update);
    evqSubscribeEvent(this, EVT_CharKeyDown, gc_keyPressed);
}

void gc_destroy(gameObject_t* this)
{
    gameControllerData_t* gd = this->data;
    free(gd->player);
}

gameObject_t* createGameController()
{
    gameObject_t* obj = object();
    obj->onInit = gc_init;
    obj->onDestroy = gc_destroy;
    obj->ID = OBJECT_GAME_CONTROLLER;

    allocData(gameControllerData_t, obj, data);
    data->wave = 4;
    data->completed = 0;

    data->player = malloc(sizeof(playerData_t));
    data->player->weapon = 0;
    data->player->pos = randVector(winW, winH);

    data->player->hp = MAX_PLAYER_HP / 2;
    data->player->armour = MAX_PLAYER_ARMOUR / 3;
    data->player->frame = 0;
    data->player->lastFireFrame = 0;

    for(int i = 0; i < WEAPON_COUNT; i++) {
        data->player->weaponStates[i] = 1;
        data->player->weaponCount[i] = getWeaponCount(i);
        data->player->weaponMaxCount[i] = getWeaponMaxCount(i);
    }

    return obj;
}