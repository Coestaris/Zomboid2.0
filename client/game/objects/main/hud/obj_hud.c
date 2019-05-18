//
// Created by maxim on 5/10/19.
//

#include "obj_hud.h"
#include "../../weapon.h"

color_t hudColor;
int hudDepth = 5;
tex_t* wepSlotTex;
tex_t* hpTex;
tex_t* armourTex;
tex_t* progressBarTex;
tex_t* borderTex;
tex_t* menuTex;

char* strings[WEAPON_COUNT] = {
        "1", "2", "3", "4", "5", "6"
};

#define weaponTextLen 20
#define grenadeTextLen 2
#define hpTextLen 5
#define armourTextLen 5
#define waveTextLen 10
#define completedTextLen 15
#define scoreTextLen 10

char weaponText[weaponTextLen];
char grenadeText[grenadeTextLen];
char hpText[hpTextLen];
char armourText[armourTextLen];
char waveText[waveTextLen];
char completedText[completedTextLen];
char scoreText[scoreTextLen];

int winW, winH;

void hud_update(gameObject_t* this, void* data)
{
    playerData_t* pd = ((hudData_t*)this->data)->playerData;
    gameMobData_t* md = ((hudData_t*)this->data)->md;
    gameControllerData_t* gd = ((hudData_t*)this->data)->gcData;

    //Drawing weapon slots
    for(int i = 0; i < WEAPON_COUNT; i++) {
        int state = 0;
        if(pd->weapon == i) state = 2;
        else if(pd->weaponStates[i]) state = 1;

        dqnDrawSprite(wepSlotTex, color(1, 1, 1, hudColor.a), state, vec(winW - (wepSlotTex->width + 5) * (WEAPON_COUNT - i), winH - wepSlotTex->height), 0, 1, hudDepth);
        dqnDrawText(vec(winW - (wepSlotTex->width + 5) * (WEAPON_COUNT - i) - 4, winH + 19), state == 0 ? color(0.4, 0.4, 0.4, 1) : color(0, 0, 0, 1), hudFont, strings[i], 0.4, hudDepth + 1);
     }

    //Drawing weapon left count
    snprintf(weaponText, weaponTextLen, "%i / %i", pd->weaponCount[pd->weapon], pd->weaponMaxCount[pd->weapon]);
    double strW = fontGetStringWidth(weaponText, hudFont, 0.4);
    double strH = fontGetStringHeight(weaponText, hudFont, 0.4);
    dqnDrawText(vec(winW - strW - wepSlotTex->width + 4, winH - strH + 10), hudColor, hudFont, weaponText, 0.4, hudDepth);

    //Drawing weapon left sprites
    tex_t* leftTex = getWeaponLeftTexture(pd->weapon);
    int rows = 1;
    if(pd->weapon != 4)
    {
        double stride;
        switch(pd->weapon) {
            case 2:
                rows = 3;
                stride = 1.5;
                break;
            default:
                stride = 5;
                rows = 1;
        }

        int k = 0, j = 0;
        for(int i = 0; i < pd->weaponCount[pd->weapon]; i++)
        {
            if (k % (getWeaponCount(pd->weapon) / rows) == 0)
            {
                k = 0;
                j++;
            }
            dqnDrawSprite(leftTex, hudColor, 0, vec(winW - (leftTex->width + stride) * (k++) - 19,
                                                    winH - (leftTex->height + 3) * j - strH - wepSlotTex->height - 12),
                          0, 1, hudDepth);
        }
    }
    else
    {
        dqnDrawStretchedTexture(progressBarTex, vec(winW - 15, winH - strH - wepSlotTex->height - 50), 0, hudColor,
                -(225 / (double)progressBarTex->width * (pd->weaponCount[pd->weapon]) / (double)getWeaponCount(pd->weapon)),
                1.15, hudDepth);
    }

    //Drawing weapon texture
    tex_t* wepTex = getWeaponTexture(pd->weapon);
    dqnDrawSprite(wepTex, hudColor, 0, vec(winW - wepTex->width + 20, winH - wepTex->height - strH - (leftTex->height + 3) * rows), 0, 1, hudDepth);

    //Drawing grenade texture
    tex_t* grenTex = getGrenTexture();
    dqnDrawSprite(grenTex, hudColor, 0, vec(winW - (wepSlotTex->width + 5)* WEAPON_COUNT - 20, winH - wepSlotTex->height / 2.0 - 10), 0, 1, hudDepth);

    //Drawing grenade left text
    snprintf(grenadeText, grenadeTextLen, "%i", pd->grenades);
    strW = fontGetStringWidth(grenadeText, hudFont, 0.4);
    dqnDrawText(vec(winW - (wepSlotTex->width + 5)* WEAPON_COUNT - 28 - strW, winH - wepSlotTex->height / 2.0 + 29), hudColor, hudFont, grenadeText, 0.4, hudDepth);

    //Drawing health texture
    int frame = (int)((MAX_PLAYER_HP - fabs(pd->hp)) / MAX_PLAYER_HP * hpTex->framesCount);
    dqnDrawSprite(hpTex, hudColor, frame >= hpTex->framesCount ? hpTex->framesCount - 1 : frame, vec(hpTex->width - 25, winH - 32), 0, 1, hudDepth);

    //Drawing health text
    snprintf(hpText, hpTextLen, "%.0lf%%", pd->hp);
    strW = fontGetStringWidth(hpText, hudFont, 0.8);
    dqnDrawText(vec(hpTex->width - 18 - strW / 2.0, winH - 10.5), hudColor, hudFont, hpText, 0.8, hudDepth);

    //Drawing armour texture
    frame = (int)((MAX_PLAYER_ARMOUR - fabs(pd->armour)) / MAX_PLAYER_ARMOUR * armourTex->framesCount);
    dqnDrawSprite(armourTex, hudColor, frame >= armourTex->framesCount ? armourTex->framesCount - 1: frame, vec(armourTex->width - 8 + hpTex->width, winH - 32), 0, 1, hudDepth);

    //Drawing armour text
    snprintf(armourText, armourTextLen, "%.0lf%%", pd->armour);
    strW = fontGetStringWidth(armourText, hudFont, 0.8);
    dqnDrawText(vec(armourTex->width - 1 - strW / 2.0 + hpTex->width, winH - 10.5), hudColor, hudFont, armourText, 0.8, hudDepth);

    //Drawing wave text
    snprintf(waveText, waveTextLen, "Wave %i", md->wave + 1);
    strW = fontGetStringWidth(waveText, hudFont, 0.6);
    dqnDrawText(vec(winW / 2.0 - strW / 2.0 + .1, 70), hudColor, hudFont, waveText, 0.6, hudDepth);

    //Drawing progress bar
    double killed =  getKilledPercentage(md);
    if(killed > 1) killed = 1;
    dqnDrawStretchedTexture(progressBarTex, vec(winW / 2.0 - 400 / 2.0, 30), 0, hudColor, 400 / (double)progressBarTex->width * killed + 1, 1.15, hudDepth);
    dqnDrawSprite(borderTex, color(0, 0, 0, hudColor.a), 0, vec(winW / 2.0, 40.8), 0, 1, hudDepth + 1);

    //Completed text
    snprintf(completedText, completedTextLen, "%.0lf%% Completed", killed * 100);
    strW = fontGetStringWidth(completedText, hudFont, 0.6);
    dqnDrawText(vec(winW / 2.0 - strW / 2.0 + .1, 120.1), hudColor, hudFont, completedText, 0.6, hudDepth);

    dqnDrawSprite(menuTex, color(1, 1, 1, hudColor.a), 0, vec(menuTex->width - 10, menuTex->height - 10), 0, 1, hudDepth + 1);

    //Score text
    snprintf(scoreText, scoreTextLen, "Score %i", pd->score);
    strW = fontGetStringWidth(scoreText, hudFont, 0.5);
    dqnDrawText(vec(winW - strW, 60), hudColor, hudFont, scoreText, 0.5, hudDepth);
}

void hud_init(gameObject_t* this)
{
    weaponCache();
    wepSlotTex = texmGetID(TEXID_HUD_WEPSLOT);
    hpTex = texmGetID(TEXID_HUD_HEART);
    armourTex = texmGetID(TEXID_HUD_SHIELD);
    progressBarTex = texmGetID(TEXID_HUD_LEFT_LASER);
    borderTex = texmGetID(TEXID_HUD_BORDER);
    menuTex = texmGetID(TEXID_HUD_MENU);

    evqSubscribeEvent(this, EVT_Update, hud_update);
    hudData_t* hd = this->data;
    int count;
    gameObject_t** objects = scmGetObjects(&count);
    for(int i = 0; i < count; i++) {
       if(objects[i]->ID == OBJECT_GAME_CONTROLLER)
       {
           hd->gcData = objects[i]->data;
           hd->playerData = hd->gcData->players[0];
           hd->md = hd->gcData->mobData[0];
       }
    }
}

gameObject_t* createHud(void)
{
    hudColor = color(175 / 255.0, 192 / 255.0, 243 / 255.0, 0.8);

    memset(weaponText, 0, weaponTextLen);
    memset(grenadeText, 0, grenadeTextLen);
    memset(hpText, 0, hpTextLen);
    memset(armourText, 0, armourTextLen);
    memset(waveText, 0, waveTextLen);
    memset(completedText, 0, completedTextLen);
    memset(scoreText, 0, scoreTextLen);

    gameObject_t* this = object();
    this->onInit = hud_init;

    allocData(hudData_t, this, data)
    return this;
}