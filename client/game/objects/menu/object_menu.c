//
// Created by maxim on 2/24/19.
//

#include "object_menu.h"

gameObject_t* main_container;
gameObject_t* sp_container;
tex_t* dummyTex;
gameObject_t* ltracer;

void menu_update(gameObject_t* this, void* data)
{
    dqnDrawSprite(dummyTex, color(0, 0, 0, 0.4), 0, vec(0, 0), 0, 2000, 1);

    ltracer->pos = getMousePos();

    ltracerUpdate();
    ltracerDraw(2);
}

void menu_button_single(menu_container_child_t* button)
{
    int w, h;
    getWinSize(&w, &h);
    char* text = "start game";
    double fontSize = 0.5;
    int tex = TEXID_MENU_SP;

    tex_t* btnTex = texmGetID(TEXID_MENU_BTN_SM);
    tex_t* tex2d = texmGetID(tex);

    gameObject_t* container = menuCreate(main_container);
    container->drawable = 1;
    container->texID = tex;
    container->pos = vec(w / 2.0, h / 2.0);

    double strW = fontGetStringWidth(text, mainFont, fontSize);
    double strH = fontGetStringHeight(text, mainFont, fontSize);

    menu_container_child_t* label = createLabel(
            vec_sub(vec(w / 2.0, h / 2.0 - tex2d->height / 2.5), vec(strW / 2.0, - strH / 2.0)),
            text, mainFont, fontSize, color(1, 1, 1, 1));

    menu_container_child_t* btnClose = createButton(
            vec(w / 2.0 - btnTex->width / 1.5, h / 2.0 + tex2d->height / 2.5),
            "back", mainFont, fontSize, color(1, 1, 1, 1), TEXID_MENU_BTN_SM, NULL);

    menu_container_child_t* btnStart = createButton(
            vec(w / 2.0 + btnTex->width / 1.5, h / 2.0 + tex2d->height / 2.5),
            "start", mainFont, fontSize, color(1, 1, 1, 1), TEXID_MENU_BTN_SM, NULL);

    btnClose->object->depth = main_container->depth + 3;
    btnStart->object->depth = main_container->depth + 3;
    label->object->depth = main_container->depth + 3;

    menuPushChild(container, label, true);
    menuPushChild(container, btnClose, true);
    menuPushChild(container, btnStart, true);

    menu_container_child_t* child = menuCreateChild(container);
    child->isContainer = true;
    container->depth = main_container->depth + 1;
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
            TEXID_MENU_BTN_SM, mainFont, .45, color(0.8, 0.8, 0.8, 1), TEXID_MENU_INDBL,
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

    menu_container_child_t* btn1 = createButton(vec(w / 2.0, hStart + 0 * hStep), "SINGLEPLAYER", mainFont, .45, color(0.8, 0.8, 0.8, 1), TEXID_MENU_BTN, menu_button_single);
    menu_container_child_t* btn2 = createButton(vec(w / 2.0, hStart + 1 * hStep), "MULTIPLAYER", mainFont, .45, color(0.8, 0.8, 0.8, 1), TEXID_MENU_BTN, menu_button_multi);
    menu_container_child_t* btn3 = createButton(vec(w / 2.0, hStart + 2 * hStep), "SETTINGS", mainFont, .45, color(0.8, 0.8, 0.8, 1), TEXID_MENU_BTN, menu_button_settings);
    menu_container_child_t* btn4 = createButton(vec(w / 2.0, hStart + 3 * hStep), "EXIT", mainFont, .45, color(0.8, 0.8, 0.8, 1), TEXID_MENU_BTN, menu_button_close);

    main_container->depth = 2;
    btn1->object->depth = main_container->depth + 1;
    btn2->object->depth = main_container->depth + 1;
    btn3->object->depth = main_container->depth + 1;
    btn4->object->depth = main_container->depth + 1;

    menuPushChild(main_container, btn1, true);
    menuPushChild(main_container, btn2, true);
    menuPushChild(main_container, btn3, true);
    menuPushChild(main_container, btn4, true);

    //Doesn't need it anymore
    //But it will draw background
    dummyTex = texmGetID(TEXID_DUMMY);
    ltracer = createTexturedAreaLT(vec(0, 0), 700, color(1, 1, 1, 0.3), texmGetID(TEXID_LIGHT), 0);
    scmPushObject(ltracer);

    evqSubscribeEvent(this, EVT_Update, menu_update);
    //scmDestroyObject(this, true);
}

gameObject_t* createMenu()
{
    gameObject_t* this = object();
    this->onInit = menu_init;
    return this;
}