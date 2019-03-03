//
// Created by maxim on 3/3/19.
//

#include "control_composer.h"

void composer_func_closeContainer(menu_container_child* this) {
    menuSetEnabled(this->parent, SETENABLE_MODE_REC_PARENTS, 1);
    menuDestroy(this->parent);
}

void composer_func_dummy_setEnabled(menu_container_child* this, int state) {
    //pass
}

menu_container_child* composer_messageBox_1btn(gameObject* parent, char* string, void* font, color_t fontColor, int tex)
{
    int w, h;
    getWinSize(&w, &h);

    int strW = glutBitmapLength(font, (unsigned char*)string);
    int strH = glutBitmapHeight(font);

    gameObject* container = menuCreate(parent);
    container->drawable = 1;
    container->texID = tex;
    container->pos = vec(w / 2.0, h / 2.0);

    menu_container_child* label = createLabel(
            vec_sub(vec(w / 2.0, h / 2.0 - 50), vec(strW / 2.0, - strH / 3.0)),
            string, font, fontColor);
    label->object->depth = parent->depth + 3;

    menu_container_child* button = createButton(
            vec_add(vec(w / 2.0, h / 2.0), vec(0, 80)), "Close", font, fontColor, TEXID_MENU_BUTTON,
            composer_func_closeContainer);
    button->object->depth = parent->depth + 3;


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

menu_container_child* composer_messageBox_2btn(gameObject* parent, char* string, void* font, color_t fontColor, int tex, void (*func1)(void), void (*func2)(void))
{

}
