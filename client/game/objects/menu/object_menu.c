//
// Created by maxim on 2/24/19.
//

#include "object_menu.h"

gameObject_t* main_container;
gameObject_t* sp_container;

void menu_button_single(menu_container_child_t* button)
{
    int w, h;
    getWinSize(&w, &h);
    char* text = "start game";
    double fontSize = 0.5;
    int tex = TEXID_MENU_INDBL;

    tex_t* tex2d = texmGetID(tex);

    gameObject_t* container = menuCreate(main_container);
    container->drawable = 1;
    container->texID = tex;
    container->pos = vec(w / 2.0, h / 2.0);

    int strW = fontGetStringWidth(text, mainFont, fontSize);
    int strH = fontGetStringHeight(text, mainFont, fontSize);

    menu_container_child_t* label = createLabel(
            vec_sub(vec(w / 2.0, h / 2.0 - tex2d->height / 4.0), vec(strW / 2.0, - strH / 3.0)),
            text, mainFont, fontSize, color(1, 1, 1, 1));
    label->object->depth = main_container->depth + 3;

    menuPushChild(container, label, true);

    menu_container_child_t* child = menuCreateChild(container);
    child->isContainer = true;
    container->depth = main_container->depth + 2;
    //child->setEnable = composer_func_dummy_setEnabled;

    menuSetEnabled(main_container, SETENABLE_MODE_REC_PARENTS, 0);
    menuPushChild(main_container, child, true);
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
            TEXID_MENU_BUTTON_SMALL, mainFont, .45, color(0.8, 0.8, 0.8, 1), TEXID_MENU_INDBL,
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
                    vec(w / 2.0, hStart + 0 * hStep), "SINGLEPLAYER", mainFont, .45,
                    color(0.8, 0.8, 0.8, 1), TEXID_MENU_BUTTON, menu_button_single),
            true);

    menuPushChild(
            main_container,
            createButton(
                    vec(w / 2.0, hStart + 1 * hStep), "MULTIPLAYER", mainFont, .45,
                    color(0.8, 0.8, 0.8, 1), TEXID_MENU_BUTTON, menu_button_multi),
            true);

    menuPushChild(
            main_container,
            createButton(
                    vec(w / 2.0, hStart + 2 * hStep), "SETTINGS", mainFont, .45,
                    color(0.8, 0.8, 0.8, 1), TEXID_MENU_BUTTON, menu_button_settings),
            true);


    menuPushChild(
            main_container,
            createButton(
                    vec(w / 2.0, hStart + 3 * hStep), "EXIT", mainFont, .45,
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