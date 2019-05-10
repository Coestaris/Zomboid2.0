//
// Created by maxim on 5/10/19.
//

#ifndef ZOMBOID2_WEAPON_H
#define ZOMBOID2_WEAPON_H

#include "../objectInclude.h"

#define WEAPON_COUNT 6

int getWeaponMaxCount(int wtype);
int getWeaponCount(int wtype);
tex_t* getWeaponTexture(int wtype);
tex_t* getWeaponLeftTexture(int wtype);

void weaponCache(void);

int harmZombie(int wtype, gameObject_t* player, gameObject_t* zombie);

#endif //ZOMBOID2_WEAPON_H
