//
// Created by maxim on 5/10/19.
//

#ifndef ZOMBOID2_WEAPON_H
#define ZOMBOID2_WEAPON_H

#include "../objectInclude.h"

#include "main/bullet/obj_bullet.h"
#include "playerData.h"

#define MAX_GRENADES 4
#define MAX_PLAYER_HP 100.0
#define MAX_PLAYER_ARMOUR 100.0

int getWeaponMaxCount(int wtype);
int getWeaponCount(int wtype);
tex_t* getPlayerTexture(int wtype);
tex_t* getGrenTexture(void);
tex_t* getWeaponTexture(int wtype);
tex_t* getWeaponLeftTexture(int wtype);
tex_t* getPlayerReloadTexture(int wtype);
int getWeaponAutoFire(int wtype);
void fire(playerData_t* player);
void reload(playerData_t* player);
double getWeaponShootingSpeed(int wtype);
double getWeaponReloadingSpeed(int wtype);

void weaponCache(void);

int harmZombie(int wtype, gameObject_t* player, gameObject_t* zombie);

#endif //ZOMBOID2_WEAPON_H
