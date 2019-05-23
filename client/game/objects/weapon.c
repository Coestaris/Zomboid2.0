//
// Created by maxim on 5/10/19.
//

#include "weapon.h"

double weapon[WEAPON_COUNT * 6] = {
    //Min dmg   | Max dmg   | Min reload  | Max reload  |   auto fire |   missRange   |  wtype
        5,            10,          30,           32,            0,          0.05,        //0 - pistol
        10,           30,          25,           28,            0,          0,           //1 - crossbow
        3,            8,           5,            6,             1,          0.1,         //2 - smg
        15,           20,          60,           65,            1,          0.12,        //3 - shotgun
        1,            1.2,         0,            0,             1,          0,           //4 - laser
        10,           10,          200,          200,           0,          0,           //5 - rpg
};

int maxWeaponCount[WEAPON_COUNT * 2] = {
    // Count  |   Max count    |  wtype
        15,         150,      //0 - pistol
        1,          60,       //1 - crossbow
        90,         500,      //2 - smg
        5,          32,       //3 - shotgun
        500,        1500,     //4 - laser
        1,          5,        //5 - rpg
};

double weaponAnimationSpeed[WEAPON_COUNT * 2] = {
    // Shooting  |  Animation   |    wtype
         1.0,          0.25,      //0 - pistol
         1.0,          0.5,       //1 - crossbow
         1.0,          0.35,      //2 - smg
         1.0,          0.25,      //3 - shotgun
         1.0,          0.5,       //4 - laser
         0.75,         0.25,      //5 - rpg
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
tex_t* shellcaseTex, *shotgunShellcaseTex;

int winW, winH;

#define  checkLaserInt(xx1, yy1, xx2, yy2)                                                   \
                        if(ltracer_getIntersection(rel.x, rel.y, dest.x, dest.y,             \
                                    vec(xx1, yy1),                                           \
                                    vec(xx2, yy2),                                           \
                                    &intX, &intY, &dist))                                    \
                        {                                                                    \
                            if (dist < minDist) {                                            \
                                minX = intX;                                                 \
                                minY = intY;                                                 \
                                minDist = dist;                                              \
                                minObject = objects[i];                                      \
                            }                                                                \
                        }

void proceedLaser(playerData_t* pd)
{
    int count = 0;
    long long frame = getFrame();

    gameObject_t** objects = scmGetObjects(&count);

    vec_t rel = relativeCoordinatesEx(getPlayerTexture(pd->weapon), pd->pos, pd->angle);
    vec_t dest = vec_add(rel, vec_mult(vec(cos(pd->angle), sin(pd->angle)), winW * M_SQRT2));

    double minX = dest.x, minY = dest.y;
    double minDist = winW * winW;
    gameObject_t* minObject = NULL;

    for(int i = 0; i < count; i++) {
        if(objects[i]->ID == OBJECT_ZOMBIE || objects[i]->ID == OBJECT_TIC    || objects[i]->ID == OBJECT_SLUG ||
           objects[i]->ID == OBJECT_BODY   || objects[i]->ID == OBJECT_SLICER) {

            double intX, intY;
            double dist;

            //checkLaserInt(0, 0, 0, objects[i]->cachedTex->height);
            double offset = 5;
            double width = objects[i]->cachedTex->height / 2.0;

            vec_t normal =  vec_mult(vec_normalize(vec_normal(vec_sub(rel, objects[i]->pos))), width);
            vec_t off = vec_add(objects[i]->pos, vec_mult(vec(cos(objects[i]->angle), sin(objects[i]->angle)), offset));

            //dqnDrawLine(vec_add(off, normal), vec_sub(off, normal), color(0, 1, 0, 1), 3);

            checkLaserInt(off.x + normal.x, off.y + normal.y, off.x - normal.x, off.y - normal.y);
        }
    }

    dqnDrawLine(rel, vec(minX, minY), color(1, 0, 0, 1), 3);

    if(minX != dest.x && minY != dest.y)
    {
        switch(minObject->ID)
        {
            case OBJECT_TIC:
                enemy_tic_harm(randRange(weapon[pd->weapon * 6 + 0], weapon[pd->weapon * 6 + 1]), minObject);
                break;
            case OBJECT_BODY:
                enemy_body_harm(randRange(weapon[pd->weapon * 6 + 0], weapon[pd->weapon * 6 + 1]), minObject);
                break;
            case OBJECT_ZOMBIE:
                enemy_zombie_harm(randRange(weapon[pd->weapon * 6 + 0], weapon[pd->weapon * 6 + 1]), minObject);
                break;
            case OBJECT_SLUG:
                enemy_slug_harm(randRange(weapon[pd->weapon * 6 + 0], weapon[pd->weapon * 6 + 1]), minObject);
                break;
            case OBJECT_GHOST:
                enemy_ghost_harm(randRange(weapon[pd->weapon * 6 + 0], weapon[pd->weapon * 6 + 1]), minObject);
                break;
            case OBJECT_SLICER:
                enemy_slicer_harm(randRange(weapon[pd->weapon * 6 + 0], weapon[pd->weapon * 6 + 1]), minObject);
                break;
            default:
                break;
        }

        if(frame % 5 == 0)
        {
            if (minObject->ID == OBJECT_SLUG)
            {
                if (randIntRange(0, 5) == 4)
                    spawnSpotBlood(1, 10, minObject->pos);
                else
                    spawnSpotSlug(1, 10, minObject->pos);
            }
            else spawnSpotBlood(1, 10, minObject->pos);
        }
    }

}

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

int getWeaponFireRate(int wtype)
{
    return (int)weapon[wtype * 6 + 3];
}

void fire(gameMobData_t* md, playerData_t* player)
{
    if(player->weaponCount[player->weapon] > 0)
    {
        if(player->state == reloading) return;

        double range = weapon[player->weapon * 6 + 5];
        double damage = randRange(weapon[player->weapon * 6 + 0], weapon[player->weapon * 6 + 1]);

        vec_t rel = relativeCoordinatesEx(getPlayerTexture(player->weapon), player->pos, player->angle);

        player->weaponCount[player->weapon]--;
        switch (player->weapon)
        {
            case 2:
            case 0:
            {
                scmPushObject(createBullet(md, rel, player->angle + randRange(-range, range), TEXID_BULLET, damage));
                vec_t pos = vec_add(rel, randVector(15, 15));
                double angle = randAngle();
                for (int i = 0; i < 5; i++)
                    srfDrawTexture(shellcaseTex, 0, color(1, 1, 1, 1), pos, angle, 1);
            }
                break;
            case 1:
                scmPushObject(createBullet(md, rel, player->angle + randRange(-range, range), TEXID_BULLET_BOLT, damage));
                break;
            case 3:
            {
                scmPushObject(
                        createBullet(md, rel, player->angle + randRange(-range, range), TEXID_BULLET_SHOTGUN, damage));
                scmPushObject(
                        createBullet(md, rel, player->angle + randRange(-range, range), TEXID_BULLET_SHOTGUN, damage));
                scmPushObject(
                        createBullet(md, rel, player->angle + randRange(-range, range), TEXID_BULLET_SHOTGUN, damage));
                scmPushObject(
                        createBullet(md, rel, player->angle + randRange(-range, range), TEXID_BULLET_SHOTGUN, damage));
            }
                break;
            case 5:
                scmPushObject(createBullet(md, rel, player->angle + randRange(-range, range), TEXID_BULLET_ROCKET, damage));
                break;
        }

        if (player->state == shooting)
        {
            player->frame = 0;
        }
        else
        {
            player->state = shooting;
        }

        if(player->weapon != 1)
        {
            if (player->lightFrame != -1)
            {
                for (int i = 0; i < player->lightFrame + 1; i++)
                    scmDestroyObject(player->fireLights[i], true);
            }

            player->lightFrame = 0;
            player->currLightSize = PLAYER_LIGHT_SIZE_START;
            player->currLightAlpha = PLAYER_LIGHT_ALPHA_START;
            pushPlayerFireLight(player);
        }

    }
    else if(player->weaponMaxCount[player->weapon] != 0 && player->state != reloading) {
        player->state = reloading;
    }
}

void pushPlayerFireLight(playerData_t* pd)
{
    gameObject_t* light = createLight(pd->pos, TEXID_LIGHT, pd->currLightSize, pd->currLightAlpha);
    pd->fireLights[pd->lightFrame++] = light;

    pd->currLightAlpha *= PLAYER_LIGHT_ALPHA_REDUCTION;
    pd->currLightSize *= PLAYER_LIGHT_SIZE_INCREASE;

    scmPushObject(light);
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

void weaponCache()
{
    for(int i = 0; i < WEAPON_COUNT; i++)
        cachedTextures[i] = texmGetID(weaponTextures[i]);

    for(int i = 0; i < WEAPON_COUNT; i++)
        cachedLeftTextures[i] = texmGetID(weaponLeftTextures[i]);

    for(int i = 0; i < WEAPON_COUNT * 2; i++)
        cachedPlayerTextures[i] = texmGetID(playerTextures[i]);

    cachedGrenTexture = texmGetID(grenTexture);
    shellcaseTex = texmGetID(TEXID_SHELLCASE);
    shotgunShellcaseTex = texmGetID(TEXID_SHELLCASE_SHOTGUN);
}
