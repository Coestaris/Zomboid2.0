//
// Created by maxim on 2/24/19.
//

#include "object_menu.h"

void menu_button_single() {
    scmLoadScene(SCENEID_GAME);
}

void menu_button_multi() {}
void menu_button_settings() {}

void menu_button_close() {
    exit(0);
}

void menu_init(gameObject* this)
{
    int w, h;
    getWinSize(&w, &h);

    double hStart = 120;
    double hStep = 100;

    scmPushObject(createButton(vec(w / 2.0, hStart + 0 * hStep), "SINGLEPLAYER",
            GLUT_BITMAP_TIMES_ROMAN_24, color(0.8, 0.8, 0.8, 1), TEXID_MENU_BUTTON, menu_button_single));
    scmPushObject(createButton(vec(w / 2.0, hStart + 1 * hStep), "MULTIPLAYER",
            GLUT_BITMAP_TIMES_ROMAN_24, color(0.8, 0.8, 0.8, 1), TEXID_MENU_BUTTON, menu_button_multi));
    scmPushObject(createButton(vec(w / 2.0, hStart + 2 * hStep), "SETTINGS",
            GLUT_BITMAP_TIMES_ROMAN_24, color(0.8, 0.8, 0.8, 1), TEXID_MENU_BUTTON, menu_button_settings));
    scmPushObject(createButton(vec(w / 2.0, hStart + 3 * hStep), "EXIT",
            GLUT_BITMAP_TIMES_ROMAN_24, color(0.8, 0.8, 0.8, 1), TEXID_MENU_BUTTON, menu_button_close));
}

gameObject* createMenu()
{
    gameObject* this = object();
    this->onInit = menu_init;
    return this;
}