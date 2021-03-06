//
// Created by maxim on 3/3/19.
//

#ifndef ZOMBOID2_CONTROL_INPUT_H
#define ZOMBOID2_CONTROL_INPUT_H

#include "../../gameLogic/gameObject.h"
#include "../../gameLogic/eventQueue.h"
#include "../../structs.h"

#include "../menu_container.h"

#define MAX_INPUT_LEN 256
#define FRAMES_BETWEEN_DELETING 5
#define FRAMES_BETWEEN_FLASH 30

typedef struct _input_data
{

    int focused;

    color_t color;

    double fontSize;
    font_t* font;

    char* str;

    int firstPressed;

    int enabled;

    long long flashStarted;
    int flash;

    color_t col;

    long long prevDeleted;

} input_data_t;

void input_event_keyDown(gameObject_t* this, void* data);
void input_event_mouse(gameObject_t* this, void* data);
void input_event_update(gameObject_t* this, void* data);
void input_init(gameObject_t* this);

menu_container_child_t* createInput(vec_t pos, color_t color, font_t* font, double fontSize, char* defstr);

#endif //ZOMBOID2_CONTROL_INPUT_H
