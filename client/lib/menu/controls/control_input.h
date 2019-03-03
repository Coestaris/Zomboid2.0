//
// Created by maxim on 3/3/19.
//

#ifndef ZOMBOID2_CONTROL_INPUT_H
#define ZOMBOID2_CONTROL_INPUT_H

#include "../../gameLogic/gameobject.h"
#include "../../gameLogic/eventQueue.h"
#include "../../structs.h"

#include "../menu_container.h"

#define MAX_INPUT_LEN 256
#define FRAMES_BETWEEN_DELETING 5

typedef struct _input_data {

    int focused;

    color_t color;
    void* font;
    char* str;

    int firstPressed;

    int enabled;

    long long prevDeleted;

} input_data;

void input_event_keyDown(gameObject* this, void* data);
void input_event_mouse(gameObject* this, void* data);
void input_event_update(gameObject* this, void* data);

void input_init(gameObject* this);
menu_container_child* createInput(vec_t pos, color_t color, void* font, char* defstr);

#endif //ZOMBOID2_CONTROL_INPUT_H
