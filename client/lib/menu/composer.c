//
// Created by maxim on 3/3/19.
//

#include "composer.h"
#include "controls/control_input.h"

void composer_func_closeContainer(menu_container_child* this) {
    button_data* bd = this->object->data;

    void (*wrapped)(void) = bd->wrappedFunc;

    menuSetEnabled(this->parent, SETENABLE_MODE_REC_PARENTS, 1);
    menuDestroy(this->parent);

    if(wrapped) {
        wrapped();
    }
}

void composer_func_dummy_setEnabled(menu_container_child* this, int state) {
    //pass
}

menu_container_child* composer_messageBox_1btn(gameObject* parent, char* string, char* s1, int btnTex,
        void* font, color_t fontColor, int tex, void (*func)(void))
{
    int w, h;
    getWinSize(&w, &h);

    int strW = glutBitmapLength(font, (unsigned char*)string);
    int strH = glutBitmapHeight(font);

    tex2d* winTexture = texmGetID(tex);

    gameObject* container = menuCreate(parent);
    container->drawable = 1;
    container->texID = tex;
    container->pos = vec(w / 2.0, h / 2.0);

    menu_container_child* label = createLabel(
            vec_sub(vec(w / 2.0, h / 2.0 - winTexture->height / 4.0), vec(strW / 2.0, - strH / 3.0)),
            string, font, fontColor);
    label->object->depth = parent->depth + 3;

    menu_container_child* button = createButton(
            vec_add(vec(w / 2.0, h / 2.0), vec(0, winTexture->height / 4.0)), s1, font, fontColor, btnTex,
            composer_func_closeContainer);
    button->object->depth = parent->depth + 3;
    ((button_data*)button->object->data)->wrappedFunc = func;

    menuPushChild(container, label, true);
    menuPushChild(container, button, true);

    menu_container_child* child = menuCreateChild(container);
    child->isContainer = true;
    child->setEnable = composer_func_dummy_setEnabled;
    container->depth = parent->depth + 2;

    menuSetEnabled(parent, SETENABLE_MODE_REC_PARENTS, 0);
    menuPushChild(parent, child, true);

    return child;
}


menu_container_child* composer_messageBox_2btn(gameObject* parent, char* text, char* s1, char* s2, int btnTex,
                                               void* font, color_t fontColor, int tex, void (*func1)(void), void (*func2)(void))
{
    int w, h;
    getWinSize(&w, &h);

    int strW = glutBitmapLength(font, (unsigned char*)text);
    int strH = glutBitmapHeight(font);

    gameObject* container = menuCreate(parent);
    container->drawable = 1;
    container->texID = tex;
    container->pos = vec(w / 2.0, h / 2.0);

    tex2d* winTexture = texmGetID(tex);
    tex2d* btnTexture = texmGetID(btnTex);

    menu_container_child* label = createLabel(
            vec_sub(vec(w / 2.0, h / 2.0 - winTexture->height / 4.0), vec(strW / 2.0, - strH / 3.0)),
            text, font, fontColor);
    label->object->depth = parent->depth + 3;

    menu_container_child* button1 = createButton(
            vec_add(vec(w / 2.0, h / 2.0), vec(btnTexture->width / 2.0 + 10, winTexture->height / 4.0)), s1, font, fontColor, btnTex,
            composer_func_closeContainer);
    button1->object->depth = parent->depth + 3;
    ((button_data*)button1->object->data)->wrappedFunc = func1;

    menu_container_child* button2 = createButton(
            vec_add(vec(w / 2.0, h / 2.0), vec(- btnTexture->width / 2.0 - 10, winTexture->height / 4.0)), s2, font, fontColor, btnTex,
            composer_func_closeContainer);
    button2->object->depth = parent->depth + 3;
    ((button_data*)button2->object->data)->wrappedFunc = func2;

    menuPushChild(container, label, true);
    menuPushChild(container, button1, true);
    menuPushChild(container, button2, true);

    menu_container_child* child = menuCreateChild(container);
    child->isContainer = true;
    child->setEnable = composer_func_dummy_setEnabled;
    container->depth = parent->depth + 2;

    menuSetEnabled(parent, SETENABLE_MODE_REC_PARENTS, 0);
    menuPushChild(parent, child, true);

    return child;
}

menu_container_child* composer_input_double(gameObject* parent, char* sl1, char* sl2, char* s1, char* s2,
        char* defStr1, char* defStr2, int btnTex, void* font, color_t fontColor,
        int tex, void (*func1)(char*), void (*func2)(char*))
{
    int w, h;
    getWinSize(&w, &h);

    int strH = glutBitmapHeight(font);

    gameObject* container = menuCreate(parent);
    container->drawable = 1;
    container->texID = tex;
    container->pos = vec(w / 2.0, h / 2.0);

    tex2d* winTexture = texmGetID(tex);
    tex2d* btnTexture = texmGetID(btnTex);

    menu_container_child* label1 = createLabel(
            vec_sub(vec(w / 2.0, h / 2.0 - winTexture->height / 4.0), vec(winTexture->width / 2.5, - strH / 3.0 + 35)),
            sl1, font, fontColor);
    label1->object->depth = parent->depth + 3;

    menu_container_child* input1 = createInput(
            vec_sub(vec(w / 2.0, h / 2.0 - winTexture->height / 4.0), vec(winTexture->width / 2.5, - strH / 3.0 - 3)),
            fontColor, font, defStr1);
    input1->object->depth = parent->depth + 3;

    menu_container_child* label2 = createLabel(
            vec_sub(vec(w / 2.0, h / 2.0 - winTexture->height / 4.0), vec(winTexture->width / 2.5, - strH / 3.0 - 55)),
            sl2, font, fontColor);
    label2->object->depth = parent->depth + 3;

    menu_container_child* button1 = createButton(
            vec_add(vec(w / 2.0, h / 2.0), vec(btnTexture->width / 2.0 + 12, winTexture->height / 3.5)), s1, font, fontColor, btnTex,
            composer_func_closeContainer);
    button1->object->depth = parent->depth + 3;
    ((button_data*)button1->object->data)->wrappedFunc = func1;

    menu_container_child* button2 = createButton(
            vec_add(vec(w / 2.0, h / 2.0), vec(- btnTexture->width / 2.0 - 12, winTexture->height / 3.5)), s2, font, fontColor, btnTex,
            composer_func_closeContainer);
    button2->object->depth = parent->depth + 3;
    ((button_data*)button2->object->data)->wrappedFunc = func2;

    menuPushChild(container, input1, true);
    menuPushChild(container, label1, true);
    menuPushChild(container, label2, true);
    menuPushChild(container, button1, true);
    menuPushChild(container, button2, true);

    menu_container_child* child = menuCreateChild(container);
    child->isContainer = true;
    child->setEnable = composer_func_dummy_setEnabled;
    container->depth = parent->depth + 2;

    menuSetEnabled(parent, SETENABLE_MODE_REC_PARENTS, 0);
    menuPushChild(parent, child, true);

    return child;
}