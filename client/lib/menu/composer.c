//
// Created by maxim on 3/3/19.
//

#include "composer.h"
#include "controls/control_input.h"

void composer_func_closeContainer(menu_container_child_t* this)
{
    button_data_t* bd = this->object->data;

    void (* wrapped)(void) = bd->wrappedFunc;

    menuSetEnabled(this->parent, SETENABLE_MODE_REC_PARENTS, 1);
    menuDestroy(this->parent);

    if (wrapped)
    {
        wrapped();
    }
}

void composer_func_dummy_setEnabled(menu_container_child_t* this, int state)
{
    //pass
}

menu_container_child_t* composer_messageBox_1btn(
        gameObject_t* parent, char* string, char* s1, int btnTex,
        font_t* font, double fontSize, color_t fontColor, int tex, void (* func)(void))
{
    int w, h;
    getWinSize(&w, &h);

    int strW = fontGetStringWidth(string, font, fontSize);
    int strH = fontGetStringHeight(string, font, fontSize);

    tex_t* winTexture = texmGetID(tex);

    gameObject_t* container = menuCreate(parent);
    container->drawable = 1;
    container->texID = tex;
    container->pos = vec(w / 2.0, h / 2.0);

    menu_container_child_t* label = createLabel(
            vec_sub(vec(w / 2.0, h / 2.0 - winTexture->height / 4.0), vec(strW / 2.0, -strH / 3.0)),
            string, font, fontSize, fontColor);
    label->object->depth = parent->depth + 3;

    menu_container_child_t* button = createButton(
            vec_add(vec(w / 2.0, h / 2.0), vec(0, winTexture->height / 4.0)), s1, font, fontSize, fontColor, btnTex,
            composer_func_closeContainer);
    button->object->depth = parent->depth + 3;
    ((button_data_t*) button->object->data)->wrappedFunc = func;

    menuPushChild(container, label, true);
    menuPushChild(container, button, true);

    menu_container_child_t* child = menuCreateChild(container);
    child->isContainer = true;
    child->setEnable = composer_func_dummy_setEnabled;
    container->depth = parent->depth + 2;

    menuSetEnabled(parent, SETENABLE_MODE_REC_PARENTS, 0);
    menuPushChild(parent, child, true);

    return child;
}


menu_container_child_t* composer_messageBox_2btn(
        gameObject_t* parent, char* text, char* s1, char* s2, int btnTex,
        font_t* font, double fontSize, color_t fontColor, int tex, void (* func1)(void), void (* func2)(void))
{
    int w, h;
    getWinSize(&w, &h);

    int strW = fontGetStringWidth(text, font, fontSize);
    int strH = fontGetStringHeight(text, font, fontSize);

    gameObject_t* container = menuCreate(parent);
    container->drawable = 1;
    container->texID = tex;
    container->pos = vec(w / 2.0, h / 2.0);

    tex_t* winTexture = texmGetID(tex);
    tex_t* btnTexture = texmGetID(btnTex);

    menu_container_child_t* label = createLabel(
            vec_sub(vec(w / 2.0, h / 2.0 - winTexture->height / 4.0), vec(strW / 2.0, -strH / 3.0)),
            text, font, fontSize, fontColor);
    label->object->depth = parent->depth + 3;

    menu_container_child_t* button1 = createButton(
            vec_add(vec(w / 2.0, h / 2.0), vec(btnTexture->width / 2.0 + 10, winTexture->height / 4.0)), s1, font,
            fontSize, fontColor, btnTex,
            composer_func_closeContainer);
    button1->object->depth = parent->depth + 3;
    ((button_data_t*) button1->object->data)->wrappedFunc = func1;

    menu_container_child_t* button2 = createButton(
            vec_add(vec(w / 2.0, h / 2.0), vec(-btnTexture->width / 2.0 - 10, winTexture->height / 4.0)), s2, font,
            fontSize, fontColor, btnTex,
            composer_func_closeContainer);
    button2->object->depth = parent->depth + 3;
    ((button_data_t*) button2->object->data)->wrappedFunc = func2;

    menuPushChild(container, label, true);
    menuPushChild(container, button1, true);
    menuPushChild(container, button2, true);

    menu_container_child_t* child = menuCreateChild(container);
    child->isContainer = true;
    child->setEnable = composer_func_dummy_setEnabled;
    container->depth = parent->depth + 2;

    menuSetEnabled(parent, SETENABLE_MODE_REC_PARENTS, 0);
    menuPushChild(parent, child, true);

    return child;
}

menu_container_child_t* composer_input_double(
        gameObject_t* parent, char* sl1, char* sl2, char* s1, char* s2,
        char* defStr1, char* defStr2, int btnTex, font_t* font, double fontSize, color_t fontColor,
        int tex, void (* func1)(char*), void (* func2)(char*))
{
    int w, h;
    getWinSize(&w, &h);

    int strH = fontGetStringHeight(sl1, font, fontSize);

    gameObject_t* container = menuCreate(parent);
    container->drawable = 1;
    container->texID = tex;
    container->pos = vec(w / 2.0, h / 2.0);

    tex_t* winTexture = texmGetID(tex);
    tex_t* btnTexture = texmGetID(btnTex);

    menu_container_child_t* label1 = createLabel(
            vec_sub(vec(w / 2.0, h / 2.0 - winTexture->height / 4.0), vec(winTexture->width / 2.5, -strH + 35)),
            sl1, font, fontSize, fontColor);
    label1->object->depth = parent->depth + 3;

    menu_container_child_t* input1 = createInput(
            vec_sub(vec(w / 2.0, h / 2.0 - winTexture->height / 4.0), vec(winTexture->width / 2.5, -strH - 3)),
            fontColor, font, fontSize, defStr1);
    input1->object->depth = parent->depth + 3;

    menu_container_child_t* label2 = createLabel(
            vec_sub(vec(w / 2.0, h / 2.0 - winTexture->height / 4.0), vec(winTexture->width / 2.5, -strH - 100)),
            sl2, font, fontSize, fontColor);
    label2->object->depth = parent->depth + 3;

    menu_container_child_t* button1 = createButton(
            vec_add(vec(w / 2.0, h / 2.0), vec(btnTexture->width / 2.0 + 12, winTexture->height / 3.5 + 15)), s1, font,
            fontSize, fontColor, btnTex,
            composer_func_closeContainer);
    button1->object->depth = parent->depth + 3;
    ((button_data_t*) button1->object->data)->wrappedFunc = func1;

    menu_container_child_t* button2 = createButton(
            vec_add(vec(w / 2.0, h / 2.0), vec(-btnTexture->width / 2.0 - 12, winTexture->height / 3.5 + 15)), s2, font,
            fontSize, fontColor, btnTex,
            composer_func_closeContainer);
    button2->object->depth = parent->depth + 3;
    ((button_data_t*) button2->object->data)->wrappedFunc = func2;

    menuPushChild(container, input1, true);
    menuPushChild(container, label1, true);
    menuPushChild(container, label2, true);
    menuPushChild(container, button1, true);
    menuPushChild(container, button2, true);

    menu_container_child_t* child = menuCreateChild(container);
    child->isContainer = true;
    child->setEnable = composer_func_dummy_setEnabled;
    container->depth = parent->depth + 2;

    menuSetEnabled(parent, SETENABLE_MODE_REC_PARENTS, 0);
    menuPushChild(parent, child, true);

    return child;
}