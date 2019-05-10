//
// Created by maxim on 5/10/19.
//

#include "weapon.h"

double weapon[WEAPON_COUNT * 4] = {
    //Min dmg   | Max dmg   | Min reload  | Max reload  |   wtype
        5,            10,          30,           32,    //0 - pistol
        10,           30,          25,           28,    //1 - crossbow
        3,            8,           5,            6,     //2 - smg
        5,            10,          60,           65,    //3 - shotgun
        5,            10,          0,            0,     //4 - laser
        100,          100,         200,          200,   //5 - rpg
};

int maxWeaponCount[WEAPON_COUNT * 2] = {
    // Count  |   Max count    |  wtype
        10,         150,      //0 - pistol
        5,          60,       //1 - crossbow
        30,         500,      //2 - smg
        5,          32,       //3 - shotgun
        1000,       1000,     //4 - laser
        1,          5,        //5 - rpg
};

int weaponTextures[WEAPON_COUNT] = {
        TEXID_WEAPON_PISTOL,
        TEXID_WEAPON_CROSSBOW,
        TEXID_WEAPON_SMG,
        TEXID_WEAPON_SHOTGUN,
        TEXID_WEAPON_LASER,
        TEXID_WEAPON_RPG
};

tex_t* cachedTextures[WEAPON_COUNT];

int getWeaponMaxCount(int wtype)
{
    return maxWeaponCount[wtype * 2 + 1];
}

int getWeaponCount(int wtype)
{
    return maxWeaponCount[wtype * 2];
}

tex_t* getWeaponTexture(int wtype)
{
    return cachedTextures[wtype];
}

int harmZombie(int wtype, gameObject_t* player, gameObject_t* zombie)
{

}

void weaponCache()
{
    for(int i = 0; i < WEAPON_COUNT; i++)
    {
        cachedTextures[i] = texmGetID(weaponTextures[i]);
        assert(cachedTextures[i]);
    }
}