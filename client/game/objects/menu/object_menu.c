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
    //dqnDrawSprite(dummyTex, color(0, 0, 0, 0.4), 0, vec(0, 0), 0, 2000, 1);
    ltracer->pos = getMousePos();
}

void menu_sp_back(menu_container_child_t* button)
{
    menuDestroy(sp_container);
    menuSetEnabled(main_container, SETENABLE_MODE_REC_PARENTS, 1);
}

void menu_sp_start(menu_container_child_t* button)
{
    menuDestroy(main_container);
    scmLoadScene(SCENEID_GAME);
}

void menu_button_single(menu_container_child_t* button)
{
    int w, h;
    getWinSize(&w, &h);
    char* text = "START GAME";
    double fontSize = 0.5;
    int tex = TEXID_MENU_SP;

    tex_t* btnTex = texmGetID(TEXID_MENU_BTN_SM);
    tex_t* tex2d = texmGetID(tex);

    color_t textCol = color(0.8, 0.8, 0.8, 1);

    sp_container = menuCreate(main_container);
    sp_container->drawable = 1;
    sp_container->texID = tex;
    sp_container->pos = vec(w / 2.0, h / 2.0);

    double strW = fontGetStringWidth(text, mainFont, fontSize);
    double strH = fontGetStringHeight(text, mainFont, fontSize);

    menu_container_child_t* label = createLabel(
            vec_sub(vec(w / 2.0, h / 2.0 - tex2d->height / 2.5), vec(strW / 2.0, -strH / 2.0 - 15)),
            text, mainFont, fontSize, textCol);

    menu_container_child_t* btnClose = createButton(
            vec(w / 2.0 - btnTex->width / 1.5, h / 2.0 + tex2d->height / 2.5),
            "BACK", mainFont, fontSize / 1.5, textCol, TEXID_MENU_BTN_SM, menu_sp_back);

    menu_container_child_t* btnStart = createButton(
            vec(w / 2.0 + btnTex->width / 1.5, h / 2.0 + tex2d->height / 2.5),
            "START", mainFont, fontSize / 1.5, textCol, TEXID_MENU_BTN_SM, menu_sp_start);

    btnClose->object->depth = main_container->depth + 4;
    btnStart->object->depth = main_container->depth + 4;
    label->object->depth = main_container->depth + 4;

    menuPushChild(sp_container, label, true);
    menuPushChild(sp_container, btnClose, true);
    menuPushChild(sp_container, btnStart, true);

    menu_container_child_t* child = menuCreateChild(sp_container);
    child->isContainer = true;
    sp_container->depth = main_container->depth + 3;
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
    int w, h;
    getWinSize(&w, &h);
    char* text = "ABOUT";
    double fontSize = 0.5;
    int tex = TEXID_MENU_SP;

    tex_t* btnTex = texmGetID(TEXID_MENU_BTN_SM);
    tex_t* tex2d = texmGetID(tex);

    color_t textCol = color(0.8, 0.8, 0.8, 1);

    sp_container = menuCreate(main_container);
    sp_container->drawable = 1;
    sp_container->texID = tex;
    sp_container->pos = vec(w / 2.0, h / 2.0);

    double strW = fontGetStringWidth(text, mainFont, fontSize);
    double strH = fontGetStringHeight(text, mainFont, fontSize);

    menu_container_child_t* label = createLabel(
            vec_sub(vec(w / 2.0, h / 2.0 - tex2d->height / 2.5), vec(strW / 2.0, -strH / 2.0 - 15)),
            text, mainFont, fontSize, textCol);

    menu_container_child_t* string1 = createLabel(vec_sub(vec(w / 2.0, h / 2.0), vec(tex2d->width / 2.0 - 20, tex2d->height / 2.5 - 70)),
            "Zomboid2.0 - small open-source glut-based", mainFont, 0.35, textCol);
    menu_container_child_t* string2 = createLabel(vec_sub(vec(w / 2.0, h / 2.0), vec(tex2d->width / 2.0 - 20, tex2d->height / 2.5 - 100)),
             "game on self-written game engine developed ", mainFont, 0.35, textCol);
    menu_container_child_t* string3 = createLabel(vec_sub(vec(w / 2.0, h / 2.0), vec(tex2d->width / 2.0 - 20, tex2d->height / 2.5 - 130)),
             "just to improve personal developing skills. ", mainFont, 0.35, textCol);
    menu_container_child_t* string4 = createLabel(vec_sub(vec(w / 2.0, h / 2.0), vec(tex2d->width / 2.0 - 20, tex2d->height / 2.5 - 200)),
             "Git: https://github.com/Coestaris/Zomboid2.0", mainFont, 0.35, textCol);

    menu_container_child_t* string5 = createLabel(vec_sub(vec(w / 2.0, h / 2.0), vec(tex2d->width / 2.0 - 20, tex2d->height / 2.5 - 290)),
            "Main contributors: ", mainFont, 0.35, textCol);
    menu_container_child_t* string6 = createLabel(vec_sub(vec(w / 2.0, h / 2.0), vec(tex2d->width / 2.0 - 20, tex2d->height / 2.5 - 320)),
            " - Coestaris (Kurylko M.): project manager, game", mainFont, 0.35, textCol);
    menu_container_child_t* string7 = createLabel(vec_sub(vec(w / 2.0, h / 2.0), vec(tex2d->width / 2.0 - 20, tex2d->height / 2.5 - 350)),
            "   engine, game logic, graphics etc.;", mainFont, 0.35, textCol);
    menu_container_child_t* string8 = createLabel(vec_sub(vec(w / 2.0, h / 2.0), vec(tex2d->width / 2.0 - 20, tex2d->height / 2.5 - 380)),
            "- vladik2738 (Dalechin V.): network engine;", mainFont, 0.35, textCol);
    menu_container_child_t* string9 = createLabel(vec_sub(vec(w / 2.0, h / 2.0), vec(tex2d->width / 2.0 - 20, tex2d->height / 2.5 - 410)),
            "- leshik_xxl (Bikerei O.): inspirer, creative.", mainFont, 0.35, textCol);
    menu_container_child_t* string10= createLabel(vec_sub(vec(w / 2.0, h / 2.0), vec(tex2d->width / 2.0 - 20, tex2d->height / 2.5 - 440)),
            "   director", mainFont, 0.35, textCol);

    menu_container_child_t* btnClose = createButton(
            vec(w / 2.0, h / 2.0 + tex2d->height / 2.5),
            "CLOSE", mainFont, fontSize / 1.5, textCol, TEXID_MENU_BTN_SM, menu_sp_back);

    string1->object->depth = main_container->depth + 4;
    string2->object->depth = main_container->depth + 4;
    string3->object->depth = main_container->depth + 4;
    string4->object->depth = main_container->depth + 4;
    string5->object->depth = main_container->depth + 4;
    string6->object->depth = main_container->depth + 4;
    string7->object->depth = main_container->depth + 4;
    string8->object->depth = main_container->depth + 4;
    string9->object->depth = main_container->depth + 4;
    string10->object->depth = main_container->depth + 4;
    btnClose->object->depth = main_container->depth + 4;
    label->object->depth = main_container->depth + 4;

    menuPushChild(sp_container, string1, true);
    menuPushChild(sp_container, string2, true);
    menuPushChild(sp_container, string3, true);
    menuPushChild(sp_container, string4, true);
    menuPushChild(sp_container, string5, true);
    menuPushChild(sp_container, string6, true);
    menuPushChild(sp_container, string7, true);
    menuPushChild(sp_container, string8, true);
    menuPushChild(sp_container, string9, true);
    menuPushChild(sp_container, string10, true);

    menuPushChild(sp_container, label, true);
    menuPushChild(sp_container, btnClose, true);

    menu_container_child_t* child = menuCreateChild(sp_container);
    child->isContainer = true;
    sp_container->depth = main_container->depth + 3;
    //child->setEnable = composer_func_dummy_setEnabled;

    menuSetEnabled(main_container, SETENABLE_MODE_REC_PARENTS, 0);
    menuPushChild(main_container, child, true);
}

void menu_button_close(menu_container_child_t* button)
{
    exit(0);
}

void menu_init(gameObject_t* this)
{
    int w, h;
    getWinSize(&w, &h);

    const double hStart = 150;
    const double hStep = 120;

    main_container = menuCreate(NULL);
    scmPushObject(main_container);

    menu_container_child_t* btn1 = createButton(vec(w / 2.0, hStart + 0 * hStep), "SINGLEPLAYER", mainFont, .45,
                                                color(0.8, 0.8, 0.8, 1), TEXID_MENU_BTN, menu_button_single);
    menu_container_child_t* btn2 = createButton(vec(w / 2.0, hStart + 1 * hStep), "MULTIPLAYER", mainFont, .45,
                                                color(0.8, 0.8, 0.8, 1), TEXID_MENU_BTN, menu_button_multi);
    menu_container_child_t* btn3 = createButton(vec(w / 2.0, hStart + 2 * hStep), "ABOUT", mainFont, .45,
                                                color(0.8, 0.8, 0.8, 1), TEXID_MENU_BTN, menu_button_settings);
    menu_container_child_t* btn4 = createButton(vec(w / 2.0, hStart + 3 * hStep), "EXIT", mainFont, .45,
                                                color(0.8, 0.8, 0.8, 1), TEXID_MENU_BTN, menu_button_close);

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