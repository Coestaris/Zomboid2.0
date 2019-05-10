//
// Created by maxim on 5/10/19.
//

#include "obj_hud.h"
#include "../../weapon.h"

color_t hudColor;
int hudDepth = 5;
tex_t* wepSlotTex;

int winW, winH;

void hud_update(gameObject_t* this, void* data)
{
    playerData_t* pd = ((hudData_t*)this->data)->playerData;
    tex_t* wepTex = getWeaponTexture(pd->weapon);
    dqnDrawSprite(wepTex, hudColor, 0, vec(winW - wepTex->width, winH - wepTex->height), 0, 1, hudDepth);

    for(int i = 0; i < WEAPON_COUNT; i++) {
        int state = 0;
        if(pd->weapon == i) state = 2;
        else if(pd->weaponStates[i]) state = 1;

        dqnDrawSprite(wepSlotTex, color(1, 1, 1, hudColor.a), state, vec(winW - (wepSlotTex->width + 5) * (WEAPON_COUNT - i), winH - wepSlotTex->height), 0, 1, hudDepth);
    }
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

    gameObject_t* this = object();
    this->onInit = hud_init;

    allocData(hudData_t, this, data)
    return this;
}