//
// Created by maxim on 3/2/19.
//

#include "control_label.h"

void label_event_update(gameObject_t* this, void* data) {
    label_data_t* ld = this->data;
    dqnDrawText(this->pos, ld->col, ld->font, ld->string, this->depth + 1);
}

void label_init(gameObject_t* this) {
    evqSubscribeEvent(this, EVT_Update, label_event_update);
}

void label_setEnable(menu_container_child_t* child, int state) {
    // pass
}

menu_container_child_t* createLabel(vec_t pos, char* string, void* font, color_t col)
{
    gameObject_t* this = object();
    this->pos = pos;
    this->onInit = label_init;

    this->data = malloc(sizeof(label_data_t));
    label_data_t* ld = this->data;

    ld->string = string;
    ld->font = font;
    ld->col = col;

    menu_container_child_t* child = menuCreateChild(this);
    child->setEnable = label_setEnable;
    child->setFocused = NULL;

    return child;
}