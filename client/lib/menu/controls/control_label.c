//
// Created by maxim on 3/2/19.
//

#include "control_label.h"

void label_event_update(gameObject* this, void* data) {
    label_data* ld = this->data;
    dqnDrawText(this->pos, ld->col, ld->font, ld->string, this->depth + 1);
}

void label_init(gameObject* this) {
    evqSubscribeEvent(this, EVT_Update, label_event_update);
}

void label_setEnable(menu_container_child* child, int state) {
    // pass
}

menu_container_child* createLabel(vec_t pos, char* string, void* font, color_t col)
{
    gameObject* this = object();
    this->pos = pos;
    this->onInit = label_init;

    this->data = malloc(sizeof(label_data));
    label_data* ld = this->data;

    ld->string = string;
    ld->font = font;
    ld->col = col;

    menu_container_child* child = menuCreateChild(this);
    child->setEnable = label_setEnable;
    child->setFocused = NULL;

    return child;
}