//
// Created by maxim on 3/2/19.
//

#ifndef ZOMBOID2_CONTROL_LABEL_H
#define ZOMBOID2_CONTROL_LABEL_H

#include "../../structs.h"
#include "../../gameLogic/gameobject.h"
#include "../menu_container.h"

typedef struct _label_data {
    char* string;

    double fontSize;
    font_t*font;

    color_t col;
} label_data_t;

void label_event_update(gameObject_t* this, void* data);
void label_init(gameObject_t* this);
void label_setEnable(menu_container_child_t* child, int state);

menu_container_child_t* createLabel(vec_t pos, char* string, font_t* font, double fontSize, color_t col);


#endif //ZOMBOID2_CONTROL_LABEL_H
