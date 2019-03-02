//
// Created by maxim on 3/2/19.
//

#ifndef ZOMBOID2_OBJECT_CONTROL_LABEL_H
#define ZOMBOID2_OBJECT_CONTROL_LABEL_H

#include "../../../objectInclude.h"

typedef struct _label_data {
    char* string;
    void *font;
    color_t col;
} label_data;

void label_event_update(gameObject* this, void* data);
void label_init(gameObject* this);
void label_setEnable(menu_container_child* child, int state);

menu_container_child* createLabel(vec_t pos, char* string, void* font, color_t col);


#endif //ZOMBOID2_OBJECT_CONTROL_LABEL_H
