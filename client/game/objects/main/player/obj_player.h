//
// Created by maxim on 1/23/19.
//

#ifndef ZOMBOID2_OBJ_TEST_H
#define ZOMBOID2_OBJ_TEST_H

#include "../../../objectInclude.h"

#include "../enemy/obj_enemy_zombie.h"
#include "../bullet/obj_bullet.h"
#include "../flashlight/obj_flashlight.h"
#include "../light/obj_light_tracer.h"
#include "../../weapon.h"

#define PLAYER_FIRE_RATE 5

#define PLAYER_MOVE_X 2.5
#define PLAYER_MOVE_Y 2.5

#define PLAYER_SHAKE_START 0.6
#define PLAYER_SHAKE_MIN 0.5
#define PLAYER_SHAKE_REDUCTION 0.7

#define PLAYER_LIGHT_ALPHA_START 0.08
#define PLAYER_LIGHT_ALPHA_REDUCTION .85
#define PLAYER_LIGHT_SIZE_START .5
#define PLAYER_LIGHT_SIZE_INCREASE 1.85

#define PLAYER_MAXLIGHTS 3

#define PLAYER_BACKLIGHT_SIZE .5
#define PLAYER_BACKLIGHT_ALPHA .04

typedef struct _playerData
{

    int prevAnimationFrame;

    //Light and shake visuals
    double currLightSize;
    double currLightAlpha;
    double currShake;

    int currentLightsCount;
    int enabledFlashLight;

    gameObject_t* fireLights[PLAYER_MAXLIGHTS];
    gameObject_t* backLight;
    gameObject_t* flashlight;
    //=======

    //Weapon stuff
    long long lastFireFrame;

    int weapon;
    uint8_t weaponStates[WEAPON_COUNT];
    int weaponCount[WEAPON_COUNT];
    int weaponMaxCount[WEAPON_COUNT];
    int grenades;

    //Gameplay stuff
    double hp;
    double armour;
    int points;


} playerData_t;

void player_event_keyPressed(gameObject_t* this, void* data);
void player_init(gameObject_t* object);
void player_event_update(gameObject_t* object, void* data);
gameObject_t* createPlayer();

#endif //ZOMBOID2_OBJ_TEST_H
