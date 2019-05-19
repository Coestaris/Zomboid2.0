//
// Created by maxim on 5/11/19.
//

#ifndef ZOMBOID2_PLAYERDATA_H
#define ZOMBOID2_PLAYERDATA_H

#include "../objectInclude.h"

#define WEAPON_COUNT 6
#define PLAYER_MOVE_X 2.5
#define PLAYER_MOVE_Y 2.5
#define MAX_PLAYER_HP 100.0
#define MAX_PLAYER_ARMOUR 100.0

#define PLAYER_LIGHT_ALPHA_START 0.08
#define PLAYER_LIGHT_ALPHA_REDUCTION .85
#define PLAYER_LIGHT_SIZE_START .5
#define PLAYER_LIGHT_SIZE_INCREASE 1.85

#define PLAYER_MAXLIGHTS 3
#define PLAYER_BACKLIGHT_SIZE .5
#define PLAYER_BACKLIGHT_ALPHA .04

typedef enum _playerState {
    nothing, shooting, reloading

} playerState_t;

typedef struct _playerData
{
    vec_t pos;
    double angle;

    double frame;
    long long lastFireFrame;

    playerState_t state;

    //light stuff
    double currLightSize;
    double currLightAlpha;
    int lightFrame;
    gameObject_t* fireLights[PLAYER_MAXLIGHTS];
    //gameObject_t* backLight;
    //gameObject_t* flashlight;

    //Weapon stuff
    int weapon;
    uint8_t weaponStates[WEAPON_COUNT];
    int weaponCount[WEAPON_COUNT];
    int weaponMaxCount[WEAPON_COUNT];
    int grenades;

    //Gameplay stuff
    double hp;
    double armour;
    int score;

} playerData_t;

#endif //ZOMBOID2_PLAYERDATA_H
