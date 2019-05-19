//
// Created by maxim on 5/10/19.
//

#ifndef ZOMBOID2_WEAPON_H
#define ZOMBOID2_WEAPON_H

#include "../objectInclude.h"

#include "main/enemy/obj_enemy_zombie.h"
#include "main/bullet/obj_bullet.h"
#include "playerData.h"

#define MAX_GRENADES 4

void pushPlayerFireLight(playerData_t* pd);
int getWeaponMaxCount(int wtype);
int getWeaponCount(int wtype);
tex_t* getPlayerTexture(int wtype);
tex_t* getGrenTexture(void);
tex_t* getWeaponTexture(int wtype);
tex_t* getWeaponLeftTexture(int wtype);
tex_t* getPlayerReloadTexture(int wtype);
int getWeaponAutoFire(int wtype);
void fire(gameMobData_t* md, playerData_t* player);
void reload(playerData_t* player);
double getWeaponShootingSpeed(int wtype);
double getWeaponReloadingSpeed(int wtype);
int getWeaponFireRate(int wtype);
void proceedLaser(playerData_t* pd);

void weaponCache(void);

#endif //ZOMBOID2_WEAPON_H
