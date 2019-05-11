//
// Created by maxim on 5/10/19.
//

#include "weapon.h"

double weapon[WEAPON_COUNT * 6] = {
    //Min dmg   | Max dmg   | Min reload  | Max reload  |   auto fire |   missRange   |  wtype
        5,            10,          30,           32,            0,          0.05,        //0 - pistol
        10,           30,          25,           28,            1,          0,          //1 - crossbow
        3,            8,           5,            6,             1,          0,          //2 - smg
        5,            10,          60,           65,            1,          0,          //3 - shotgun
        5,            10,          0,            0,             1,          0,          //4 - laser
        100,          100,         200,          200,           1,          0,          //5 - rpg
};

int maxWeaponCount[WEAPON_COUNT * 2] = {
    // Count  |   Max count    |  wtype
        15,         150,      //0 - pistol
        5,          60,       //1 - crossbow
        90,         500,      //2 - smg
        5,          32,       //3 - shotgun
        1000,       1000,     //4 - laser
        1,          5,        //5 - rpg
};

double weaponAnimationSpeed[WEAPON_COUNT * 2] = {
    // Shooting  |  Animation   |    wtype
         1.0,          0.25,      //0 - pistol
         1.0,          0.5,       //1 - crossbow
         1.0,          0.5,       //2 - smg
         1.0,          0.5,       //3 - shotgun
         1.0,          0.5,       //4 - laser
         1.0,          0.5,       //5 - rpg
};

int playerTextures[WEAPON_COUNT * 2] = {
        TEXID_PLAYER_PISTOL, TEXID_PLAYER_PISTOL_RELOAD,
        TEXID_PLAYER_CROSS,  TEXID_PLAYER_CROSS_RELOAD,
        TEXID_PLAYER_SMG,    TEXID_PLAYER_SMG_RELOAD,
        TEXID_PLAYER_SHOT,   TEXID_PLAYER_SHOT_RELOAD,
        TEXID_PLAYER_LASER,  TEXID_PLAYER_LASER,
        TEXID_PLAYER_RPG,    TEXID_PLAYER_RPG_RELOAD,
};

int weaponTextures[WEAPON_COUNT] = {
        TEXID_WEAPON_PISTOL,
        TEXID_WEAPON_CROSSBOW,
        TEXID_WEAPON_SMG,
        TEXID_WEAPON_SHOTGUN,
        TEXID_WEAPON_LASER,
        TEXID_WEAPON_RPG
};

int weaponLeftTextures[WEAPON_COUNT] = {
        TEXID_HUD_LEFT_BULLET,
        TEXID_HUD_LEFT_BOLT,
        TEXID_HUD_LEFT_BULLET,
        TEXID_HUD_LEFT_SHELL,
        TEXID_HUD_LEFT_LASER,
        TEXID_HUD_LEFT_ROCKET,
};

int grenTexture = TEXID_HUD_LEFT_GRENADE;

tex_t* cachedPlayerTextures[WEAPON_COUNT * 2];
tex_t* cachedTextures[WEAPON_COUNT];
tex_t* cachedLeftTextures[WEAPON_COUNT];
tex_t* cachedGrenTexture;

void reload(playerData_t* player)
{
    if(player->weaponMaxCount[player->weapon] > 0)
    {
        player->weaponMaxCount[player->weapon] += player->weaponCount[player->weapon];

        if(player->weaponMaxCount[player->weapon] - getWeaponCount(player->weapon) < 0)
        {
            player->weaponCount[player->weapon] = player->weaponMaxCount[player->weapon];
            player->weaponMaxCount[player->weapon] = 0;
        }
        else
        {
            player->weaponMaxCount[player->weapon] -= getWeaponCount(player->weapon);
            player->weaponCount[player->weapon] = getWeaponCount(player->weapon);
        }
    }
}

void fire(playerData_t* player)
{
    if(player->weaponCount[player->weapon] > 0 && player->state != reloading)
    {
        double range = weapon[player->weapon * 6 + 5];
        vec_t rel = relativeCoordinatesEx(getPlayerTexture(player->weapon), player->pos, player->angle);

        player->weaponCount[player->weapon]--;
        switch (player->weapon)
        {
            case(0):
                scmPushObject(createBullet(rel, player->angle + randRange(-range, range)));
            default:
                break;
        }

        if(player->state == shooting) {
            player->frame = 0;
        }
        else {
            player->state = shooting;
        }
    }
}

int getWeaponAutoFire(int wtype)
{
    return (int)weapon[wtype * 6 + 4];
}

int getWeaponMaxCount(int wtype)
{
    return maxWeaponCount[wtype * 2 + 1];
}

int getWeaponCount(int wtype)
{
    return maxWeaponCount[wtype * 2];
}

tex_t* getPlayerReloadTexture(int wtype)
{
    return cachedPlayerTextures[wtype * 2 + 1];
}

tex_t* getPlayerTexture(int wtype)
{
    return cachedPlayerTextures[wtype * 2];
}

tex_t* getGrenTexture(void)
{
    return cachedGrenTexture;
}

tex_t* getWeaponTexture(int wtype)
{
    return cachedTextures[wtype];
}

tex_t* getWeaponLeftTexture(int wtype)
{
    return cachedLeftTextures[wtype];
}

double getWeaponShootingSpeed(int wtype)
{
    return weaponAnimationSpeed[wtype * 2];
}

double getWeaponReloadingSpeed(int wtype)
{
    return weaponAnimationSpeed[wtype * 2 + 1];
}

int harmZombie(int wtype, gameObject_t* player, gameObject_t* zombie)
{

}

void weaponCache()
{
    for(int i = 0; i < WEAPON_COUNT; i++)
        cachedTextures[i] = texmGetID(weaponTextures[i]);

    for(int i = 0; i < WEAPON_COUNT; i++)
        cachedLeftTextures[i] = texmGetID(weaponLeftTextures[i]);

    for(int i = 0; i < WEAPON_COUNT * 2; i++)
        cachedPlayerTextures[i] = texmGetID(playerTextures[i]);

    cachedGrenTexture = texmGetID(grenTexture);
}
