//
// Created by maxim on 3/3/19.
//

#include "control_input.h"

/*void input_event_keyDown(gameObject_t* this, void* data)
{
    input_data_t* id = this->data;
    keyboardEvent_t* ke = data;

    if(ke->key == 8) {
        //backspace
    }
}*/

void input_event_keyDown(gameObject_t* this, void* data)
{
    input_data_t* id = this->data;
    keyboardEvent_t* ke = data;

    if (ke->key == 8)
    {
        //backspace
        long long frame = getFrame();

        if (frame - id->prevDeleted > FRAMES_BETWEEN_DELETING)
        {
            size_t len = strlen(id->str);

            if (len != 0)
            {
                id->str[len - 1] = '\0';
            }

            id->firstPressed = true;
            id->prevDeleted = frame + 100;
        }
    }
    else if (ke->key == ' ' || (ke->key >= 0x21 && ke->key <= 0x7F))
    {
        size_t len = strlen(id->str);
        if (len < MAX_INPUT_LEN)
        {
            id->str[len] = (char) ke->key;
            id->str[len + 1] = '\0';
        }
    }
}

void input_event_mouse(gameObject_t* this, void* data)
{
    input_data_t* id = this->data;
}

void input_event_update(gameObject_t* this, void* data)
{
    input_data_t* id = this->data;
    long frame = getFrame();

    dqnDrawText(this->pos, id->color, id->font, id->str, id->fontSize, this->depth);

    double height = fontGetStringHeight(id->str, id->font, id->fontSize) / 2.0 + 8;
    vec_t start = vec_add(this->pos, vec(fontGetStringWidth(id->str, id->font, id->fontSize) + 2, -height + 4));
    vec_t end = vec_add(start, vec(0, height));

    if (keyPressed(8))
    {
        if (!id->firstPressed && frame - id->prevDeleted > FRAMES_BETWEEN_DELETING)
        {

            size_t len = strlen(id->str);
            if (len != 0)
            {
                id->str[len - 1] = '\0';
            }

            id->prevDeleted = frame;
        }
    }
    else
    {
        id->firstPressed = false;
    }

    if (frame - id->flashStarted > FRAMES_BETWEEN_FLASH)
    {
        id->flashStarted = frame;
        id->flash = !id->flash;
        id->col = randColor(1);
    }

    if (id->flash)
    {
        dqnDrawLine(start, end, id->col, this->depth);
    }
}

void input_init(gameObject_t* this)
{
    evqSubscribeEvent(this, EVT_CharKeyDown, input_event_keyDown);
    //evqSubscribeEvent(this, EVT_CharKeyUp, input_event_keyUp);
    evqSubscribeEvent(this, EVT_MouseClick, input_event_mouse);
    evqSubscribeEvent(this, EVT_Update, input_event_update);
}

void input_setEnable(menu_container_child_t* child, int state)
{
    ((input_data_t*) child->object->data)->enabled = state;
}

void input_setFocused(menu_container_child_t* child, int state)
{
    ((input_data_t*) child->object->data)->focused = state;
}

menu_container_child_t* createInput(vec_t pos, color_t color, font_t* font, double fontSize, char* defstr)
{
    gameObject_t* this = object();
    this->onInit = input_init;
    this->pos = pos;

    this->data = malloc(sizeof(input_data_t));
    input_data_t* id = this->data;

    id->font = font;
    id->color = color;
    id->flash = false;
    id->flashStarted = 0;
    id->firstPressed = false;
    id->str = malloc(MAX_INPUT_LEN * sizeof(char));
    strcpy(id->str, defstr);

    menu_container_child_t* child = menuCreateChild(this);
    child->setEnable = input_setEnable;
    child->setFocused = input_setFocused;

    return child;
}