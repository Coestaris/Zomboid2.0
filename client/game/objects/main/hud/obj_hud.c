//
// Created by maxim on 5/10/19.
//

#include "obj_hud.h"
#include "../../weapon.h"

color_t hudColor;
int hudDepth = 5;
tex_t* wepSlotTex;

char* strings[WEAPON_COUNT] = {
        "1", "2", "3", "4", "5", "6"
};

char str[20];
int winW, winH;

void hud_update(gameObject_t* this, void* data)
{
    playerData_t* pd = ((hudData_t*)this->data)->playerData;


    for(int i = 0; i < WEAPON_COUNT; i++) {
        int state = 0;
        if(pd->weapon == i) state = 2;
        else if(pd->weaponStates[i]) state = 1;

        dqnDrawSprite(wepSlotTex, color(1, 1, 1, hudColor.a), state, vec(winW - (wepSlotTex->width + 5) * (WEAPON_COUNT - i), winH - wepSlotTex->height), 0, 1, hudDepth);
        dqnDrawText(vec(winW - (wepSlotTex->width + 5) * (WEAPON_COUNT - i) - 4, winH + 19), state == 0 ? color(0.4, 0.4, 0.4, 1) : color(0, 0, 0, 1), hudFont, strings[i], 0.4, hudDepth + 1);
     }


    snprintf(str, 20, "%i / %i", pd->weaponCount[pd->weapon], pd->weaponMaxCount[pd->weapon]);
    double strW = fontGetStringWidth(str, hudFont, 0.5);
    double strH = fontGetStringHeight(str, hudFont, 0.5);
    dqnDrawText(vec(winW - strW - wepSlotTex->width + 4, winH - strH + 19), hudColor, hudFont, str, 0.5, hudDepth);

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
                                                    winH - (leftTex->height + 3) * j - strH - wepSlotTex->height - 25),
                          0, 1, hudDepth);
        }
    }
    else
    {
        for(int i = 0; i < pd->weaponCount[pd->weapon] / 15; i++)
        {
            dqnDrawSprite(leftTex, hudColor, 0, vec(winW - (leftTex->width) * (i) - 19,
                                                    winH - (leftTex->height + 3) - strH - wepSlotTex->height - 25),
                          0, 1, hudDepth);
        }
    }

    tex_t* wepTex = getWeaponTexture(pd->weapon);
    dqnDrawSprite(wepTex, hudColor, 0, vec(winW - wepTex->width + 20, winH - wepTex->height - strH - (leftTex->height + 3) * rows - 10), 0, 1, hudDepth);
}

void hud_init(gameObject_t* this)
{
    weaponCache();
    wepSlotTex = texmGetID(TEXID_HUD_WEPSLOT);

    evqSubscribeEvent(this, EVT_Update, hud_update);
    hudData_t* hd = this->data;
    int count;
    gameObject_t** objects = scmGetObjects(&count);
    for(int i = 0; i < count; i++) {
        if(objects[i]->ID == OBJECT_PLAYER)
            hd->playerData = objects[i]->data;
        return;
    }

    assert(0); //Should never happen
}

gameObject_t* createHud(void)
{
    hudColor = color(175 / 255.0, 192 / 255.0, 243 / 255.0, 0.6);

    memset(str, 0, 20);

    gameObject_t* this = object();
    this->onInit = hud_init;

    allocData(hudData_t, this, data)
    return this;
}