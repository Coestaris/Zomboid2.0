//
// Created by maxim on 2/23/19.
//

#ifndef ZOMBOID2_CONTROL_BUTTON_H
#define ZOMBOID2_CONTROL_BUTTON_H

#include "../../structs.h"
#include "../../gameLogic/gameHelpers.h"
#include "../../gameLogic/gameobject.h"
#include "../menu_container.h"

typedef struct _button_data {
    char* string;
    void *font;
    color_t col;

    int height;
    int width;

    int enabled;
    menu_container_child_t* self;

    void (*func)(menu_container_child_t*);
    void (*wrappedFunc)(void);

} button_data_t;

void button_event_update(gameObject_t* this, void* data);
void button_event_mouseClick(gameObject_t* this, void* data);
void button_init(gameObject_t* this);
void button_setEnable(menu_container_child_t* child, int state);

menu_container_child_t* createButton(vec_t pos, char* string, void* font, color_t col, int tex, void (*func)(menu_container_child_t*));

#endif //ZOMBOID2_CONTROL_BUTTON_H
