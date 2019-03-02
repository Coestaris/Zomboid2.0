//
// Created by maxim on 2/23/19.
//

#ifndef ZOMBOID2_OBJECT_CONTROL_BUTTON_H
#define ZOMBOID2_OBJECT_CONTROL_BUTTON_H

#include "../../../objectInclude.h"

typedef struct _button_data {
    char* string;
    void *font;
    color_t col;

    int height;
    int width;

    int enabled;
    menu_container_child* self;

    void (*func)(menu_container_child*);

} button_data;

void button_event_update(gameObject* this, void* data);
void button_event_mouseClick(gameObject* this, void* data);
void button_init(gameObject* this);
void button_setEnable(menu_container_child* child, int state);

menu_container_child* createButton(vec_t pos, char* string, void* font, color_t col, int tex, void (*func)(menu_container_child*));

#endif //ZOMBOID2_OBJECT_CONTROL_BUTTON_H
