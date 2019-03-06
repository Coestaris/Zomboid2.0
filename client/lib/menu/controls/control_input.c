//
// Created by maxim on 3/3/19.
//

#include "control_input.h"

/*void input_event_keyDown(gameObject* this, void* data)
{
    input_data* id = this->data;
    keyboardEvent* ke = data;

    if(ke->key == 8) {
        //backspace
    }
}*/

void input_event_keyDown(gameObject* this, void* data)
{
    input_data* id = this->data;
    keyboardEvent* ke = data;

    if(ke->key == 8) {
        //backspace
        long long frame = getFrame();

        if(frame - id->prevDeleted > FRAMES_BETWEEN_DELETING) {
            size_t len = strlen(id->str);

            if(len != 0) {
                id->str[len - 1] = '\0';
            }

            id->firstPressed = true;
            id->prevDeleted = frame + 100;
        }
    }
    else if(ke->key == ' ' || (ke->key >= 0x21 && ke->key <= 0x7F))
    {
        size_t len = strlen(id->str);
        if(len < MAX_INPUT_LEN) {
            id->str[len] = (char) ke->key;
            id->str[len + 1] = '\0';
        }
    }
}

void input_event_mouse(gameObject* this, void* data)
{
    input_data* id = this->data;
}

void input_event_update(gameObject* this, void* data)
{
    input_data* id = this->data;
    long frame = getFrame();

    dqnDrawText(this->pos, id->color, id->font, id->str, this->depth);

    double height = glutBitmapHeight(id->font) / 2.0 + 8;
    vec_t start = vec_add(this->pos, vec(glutBitmapLength(id->font, (const unsigned char*)id->str) + 2, - height + 4));
    vec_t end = vec_add(start, vec(0, height));

    if(keyPressed(8))
    {
        if(!id->firstPressed && frame - id->prevDeleted > FRAMES_BETWEEN_DELETING) {

            size_t len = strlen(id->str);
            if(len != 0) {
                id->str[len - 1] = '\0';
            }

            id->prevDeleted = frame;
        }
    } else {
        id->firstPressed = false;
    }

    if(frame - id->flashStarted > FRAMES_BETWEEN_FLASH) {
        id->flashStarted = frame;
        id->flash = !id->flash;
        id->col = randColor(1);
    }

    if(id->flash) {
        dqnDrawLine(start, end, id->col, this->depth);
    }
}

void input_init(gameObject* this)
{
    evqSubscribeEvent(this, EVT_CharKeyDown, input_event_keyDown);
    //evqSubscribeEvent(this, EVT_CharKeyUp, input_event_keyUp);
    evqSubscribeEvent(this, EVT_MouseClick, input_event_mouse);
    evqSubscribeEvent(this, EVT_Update, input_event_update);
}

void input_setEnable(menu_container_child* child, int state) {
    ((input_data*)child->object->data)->enabled = state;
}

void input_setFocused(menu_container_child* child, int state) {
    ((input_data*)child->object->data)->focused = state;
}

menu_container_child* createInput(vec_t pos, color_t color, void* font, char* defstr)
{
    gameObject* this = object();
    this->onInit = input_init;
    this->pos = pos;

    this->data = malloc(sizeof(input_data));
    input_data* id = this->data;

    id->font = font;
    id->color = color;
    id->flash = false;
    id->flashStarted = 0;
    id->firstPressed = false;
    id->str = malloc(MAX_INPUT_LEN * sizeof(char));
    strcpy(id->str, defstr);

    menu_container_child* child = menuCreateChild(this);
    child->setEnable = input_setEnable;
    child->setFocused = input_setFocused;

    return child;
}