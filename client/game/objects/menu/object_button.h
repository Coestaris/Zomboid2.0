//
// Created by maxim on 2/23/19.
//

#ifndef ZOMBOID2_OBJECT_BUTTON_H
#define ZOMBOID2_OBJECT_BUTTON_H

#include "../../objectInclude.h"

typedef struct _button_data {
    const char* string;
    void *font;
    color_t col;

    int height;
    int width;
    void (*func)();

} button_data;

gameObject* createButton(vec_t pos, const char* string, void* font, color_t col, int tex, void (*func)());

#endif //ZOMBOID2_OBJECT_BUTTON_H
