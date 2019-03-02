//
// Created by maxim on 2/24/19.
//

#include "object_menu.h"

gameObject* main_container;

void menu_button_single(menu_container_child* button)
{
    menuDestroy(main_container);
    scmLoadScene(SCENEID_GAME);
}

void menu_button_multi(menu_container_child* button)
{
    menu_container_child* info = composer_messageBox_1btn(main_container, (char*)"Hello gay!",
            GLUT_BITMAP_TIMES_ROMAN_24, color(1, 1, 1, 1), TEXID_MENU_OUT);
}

void menu_button_settings(menu_container_child* button)
{
    menuDestroy(main_container);
}

void menu_button_close(menu_container_child* button)
{
    exit(0);
}

void menu_init(gameObject* this)
{
    int w, h;
    getWinSize(&w, &h);

    double hStart = 120;
    double hStep = 100;

    main_container = menuCreate();
    scmPushObject(main_container);

    menuPushChild(
            main_container,
            createButton(
                    vec(w / 2.0, hStart + 0 * hStep), "SINGLEPLAYER", GLUT_BITMAP_TIMES_ROMAN_24,
                    color(0.8, 0.8, 0.8, 1), TEXID_MENU_BUTTON, menu_button_single),
            true);

    menuPushChild(
            main_container,
            createButton(
                    vec(w / 2.0, hStart + 1 * hStep), "MULTIPLAYER", GLUT_BITMAP_TIMES_ROMAN_24,
                    color(0.8, 0.8, 0.8, 1), TEXID_MENU_BUTTON, menu_button_multi),
            true);

    menuPushChild(
            main_container,
            createButton(
                    vec(w / 2.0, hStart + 2 * hStep), "SETTINGS", GLUT_BITMAP_TIMES_ROMAN_24,
                    color(0.8, 0.8, 0.8, 1), TEXID_MENU_BUTTON, menu_button_settings),
            true);


    menuPushChild(
            main_container,
            createButton(
                    vec(w / 2.0, hStart + 3 * hStep), "EXIT", GLUT_BITMAP_TIMES_ROMAN_24,
                    color(0.8, 0.8, 0.8, 1), TEXID_MENU_BUTTON, menu_button_close),
            true);
}

gameObject* createMenu()
{
    gameObject* this = object();
    this->onInit = menu_init;
    return this;
}