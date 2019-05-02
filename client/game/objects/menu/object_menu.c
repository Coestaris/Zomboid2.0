//
// Created by maxim on 2/24/19.
//

#include "object_menu.h"

gameObject_t* main_container;

void menu_button_single(menu_container_child_t* button)
{
    menuDestroy(main_container);
    scmLoadScene(SCENEID_GAME);
}


/*
void menu_button_gay_no() {
    composer_messageBox_1btn(main_container, (char*)"SAD =c", "EXIT", TEXID_MENU_BUTTON,
                             GLUT_BITMAP_TIMES_ROMAN_24, color(0.8, 0.8, 0.8, 1), TEXID_MENU_OUT, NULL);

    composer_messageBox_2btn(main_container, (char*)"Are you gay?", "YES", "NO", TEXID_MENU_BUTTON,
            GLUT_BITMAP_TIMES_ROMAN_24, color(0.8, 0.8, 0.8, 1), TEXID_MENU_OUT,
            menu_button_gay_yes, menu_button_gay_no);
}
*/

void menu_button_multi(menu_container_child_t* button)
{
    composer_input_double(main_container, "IP address", "Port", "OK", "Cancel", "127.0.0.1", "1234",
            TEXID_MENU_BUTTON_SMALL, GLUT_BITMAP_TIMES_ROMAN_24, color(0.8, 0.8, 0.8, 1), TEXID_MENU_INDBL,
            NULL, NULL);
}

void menu_button_settings(menu_container_child_t* button)
{
    menuDestroy(main_container);
}

void menu_button_close(menu_container_child_t* button)
{
    exit(0);
}

void menu_init(gameObject_t* this)
{
    int w, h;
    getWinSize(&w, &h);

    const double hStart = 120;
    const double hStep = 100;

    main_container = menuCreate(NULL);
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

    //Doesn't need it anymore
    scmDestroyObject(this, true);
}

gameObject_t* createMenu()
{
    gameObject_t* this = object();
    this->onInit = menu_init;
    return this;
}