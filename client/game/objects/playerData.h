//
// Created by maxim on 5/11/19.
//

#ifndef ZOMBOID2_PLAYERDATA_H
#define ZOMBOID2_PLAYERDATA_H

#include "../objectInclude.h"

#define WEAPON_COUNT 6
#define PLAYER_MOVE_X 2.5
#define PLAYER_MOVE_Y 2.5

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
